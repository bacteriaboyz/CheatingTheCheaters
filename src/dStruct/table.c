#include <stdlib.h>

#include "hash.h"
#include "table.h"

static bool tableKeysEqual(tableKey *k1, tableKey *k2)
{
    if (k1->type != k2->type)
    {
        return false;
    }
    else if (k1->type == INDEX)
    {
        return k1->data.idx == k2->data.idx;
    }

    return k1->data.bacterium == k2->data.bacterium;
}

bool tableIsEmpty(tableHash *table)
{
    return table->num == 0;
}

void tableInit(tableHash *table, cInt len, errorCode *error)
{
    cInt len_idx = 0;

    if (len > table_sizes[table_num_sizes - 1])
    {
        *error = MEM;
        return;
    }

    for (;; ++len_idx)
    {
        if (len <= table_sizes[len_idx])
        {
            break;
        }
    }

    if (!(table->slots = calloc(len, sizeof(tableSlot))))
    {
        *error = MEM;
        return;
    }

    table->num = 0;
    table->num_ghosts = 0;
    table->len = table_sizes[len_idx];
    table->len_idx = len_idx;

    *error = SUCCESS;
}

// Returns true if we've added an entry to a fresh position.

static bool tableUnsafeAdd(
                            tableSlot *slots,
                            cInt table_len,
                            tableKey key,
                            tableVal val,
                            cInt key_len
                          )
{
    cInt table_idx = hash32((char *)&key.data, key_len) % table_len;
    cInt search_idx = table_idx;

    for (;;)
    {
        if (
            !slots[search_idx].used ||
            tableKeysEqual(&slots[search_idx].key, &key)
           )
        {
            break;
        }
        else if (++search_idx == table_len)
        {
            search_idx = 0;
        }
    }

    tableSlot *slot = slots + search_idx;

    slot->key = key;
    slot->val = val;
    slot->used = 1;

    if (slot->used_before)
    {
        return false;
    }

    slot->used_before = 1;
    return true;
}

void tableAdd(
                tableHash *table,
                tableKey key,
                tableVal val,
                cInt key_len,
                errorCode *error
             )
{
    // If we've reached the load factor threshold, resize.

    if (table->num >= table->len / 2)
    {
        if (++table->len_idx == table_num_sizes)
        {
            *error = MEM;
            return;
        }

        cInt new_len = table_sizes[table->len_idx];
        tableSlot *new_slots = calloc(new_len, sizeof(tableSlot));

        if (!new_slots)
        {
            *error = MEM;
            return;
        }

        for (cInt i = 0; i < table->len; ++i)
        {
            tableSlot *slot = table->slots + i;

            if (slot->used)
            {
                tableUnsafeAdd(
                                new_slots,
                                new_len,
                                slot->key,
                                slot->val,
                                key_len
                               );
            }
        }

        free(table->slots);

        table->slots = new_slots;
        table->num_ghosts = 0;
        table->len = new_len;
    }

    if (tableUnsafeAdd(table->slots, table->len, key, val, key_len))
    {
        --table->num_ghosts;
    }
    ++table->num;

    *error = SUCCESS;
}

static tableSlot *tablePosLookup(tableHash *table, tableKey key, cInt key_len)
{
    cInt table_idx = hash32((char *)&key.data, key_len) % table->len;
    cInt search_idx = table_idx;

    do
    {
        tableSlot *slot = table->slots + search_idx++;

        if (!slot->used_before)
        {
            return NULL;
        }
        else if (slot->used && tableKeysEqual(&slot->key, &key))
        {
            return slot;
        }
        else if (search_idx == table->len)
        {
            search_idx = 0;
        }
    } while (search_idx != table_idx);

    return NULL;
}

tableVal tableLookup(
                        tableHash *table,
                        tableKey key,
                        cInt key_len,
                        errorCode *error
                    )
{
    tableSlot *slot = tablePosLookup(table, key, key_len);
    tableVal garbage;

    if (slot)
    {
        *error = SUCCESS;
        return slot->val;
    }

    *error = NOT_FOUND;
    return garbage;
}

void tableDel(tableHash *table, tableKey key, cInt key_len, errorCode *error)
{
    tableSlot *slot = tablePosLookup(table, key, key_len);

    if (slot)
    {
        slot->used = 0;
        ++table->num_ghosts;
        --table->num;

        // If there are too many "ghosts," rebuild the table.

        if (table->len >= 23 && table->num_ghosts >= table->len / 4)
        {
            tableSlot *new_slots = calloc(table->len, sizeof(tableSlot));

            if (!new_slots)
            {
                *error = MEM;
                return;
            }

            for (cInt i = 0; i < table->len; ++i)
            {
                tableSlot *slot = table->slots + i;

                if (slot->used)
                {
                    tableUnsafeAdd(
                                    new_slots,
                                    table->len,
                                    slot->key,
                                    slot->val,
                                    key_len
                                   );
                }
            }

            free(table->slots);

            table->slots = new_slots;
            table->num_ghosts = 0;
        }

        *error = SUCCESS;
    }
    else
    {
        *error = NOT_FOUND;
    }
}

void tableFree(tableHash *table)
{
    free(table->slots);
}

void tableAddBucket(
                    tableHash *table,
                    cInt idx,
                    bucketBac *bucket,
                    errorCode *error
                   )
{
    tableKey key = { .type = INDEX, .data = { .idx = idx } };
    tableVal val = { .type = BUCKET, .data = { .bucket = bucket } };

    tableAdd(table, key, val, sizeof(cInt), error);
}

bucketBac *tableLookupBucket(tableHash *table, cInt idx, errorCode *error)
{
    tableKey key = { .type = INDEX, .data = { .idx = idx } };

    tableVal val = tableLookup(table, key, sizeof(cInt), error);

    if (*error == NOT_FOUND)
    {
        return NULL;
    }

    return val.data.bucket;
}

void tableDelBucket(tableHash *table, cInt idx, errorCode *error)
{
    tableKey key = { .type = INDEX, .data = { .idx = idx} };

    tableDel(table, key, sizeof(cInt), error);
}

void tableAddBacterium(
                       tableHash *table,
                       nodeBac *bacterium,
                       cFloat dist,
                       errorCode *error
                       )
{
    tableKey key = { .type = BACTERIUM, .data = { .bacterium = bacterium } };
    tableVal val = { .type = DISTANCE, .data = { .dist = dist } };

    tableAdd(table, key, val, sizeof(nodeBac *), error);
}

cFloat tableLookupBacterium(
                            tableHash *table,
                            nodeBac *bacterium,
                            errorCode *error
                           )
{
    tableKey key = { .type = BACTERIUM, .data = { .bacterium = bacterium } };

    tableVal val = tableLookup(table, key, sizeof(nodeBac *), error);

    if (*error == NOT_FOUND)
    {
        return 0;
    }

    return val.data.dist;
}

void tableDelBacterium(tableHash *table, nodeBac *bacterium, errorCode *error)
{
    tableKey key = { .type = BACTERIUM, .data = { .bacterium = bacterium } };

    tableDel(table, key, sizeof(nodeBac *), error);
}
