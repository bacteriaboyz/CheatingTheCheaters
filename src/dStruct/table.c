#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "table.h"

bool tableIsEmpty(tableHash *table)
{
    return table->num == 0;
}

bool tableIsInit(tableHash *table)
{
    return table->slots != NULL;
}

cInt tableCard(tableHash *table)
{
    return table->num;
}

void tableInit(
                tableHash *table,
                cInt table_len,
                cInt key_len,
                cInt val_len,
                errorCode *error
              )
{
    cInt len_idx = 0;

    if (
        table_len > table_sizes[table_num_sizes - 1] ||
        key_len > LIMITS_TABLE_ENTRY_SIZE ||
        val_len > LIMITS_TABLE_ENTRY_SIZE
       )
    {
        *error = MEM;
        return;
    }

    for (;; ++len_idx)
    {
        if (table_len <= table_sizes[len_idx])
        {
            break;
        }
    }

    table_len = table_sizes[len_idx];

    if (!(table->slots = calloc(table_len, sizeof(tableSlot))))
    {
        *error = MEM;
        return;
    }

    table->key_len = key_len;
    table->val_len = val_len;
    table->num = 0;
    table->num_ghosts = 0;
    table->len = table_len;
    table->len_idx = len_idx;

    *error = SUCCESS;
}

void tableReset(tableHash *table)
{
    memset(table->slots, 0, table->len * sizeof(tableSlot));
    table->num = 0;
    table->num_ghosts = 0;
}

/*
 * Use this function to add entries to a table without resizing. It will get
 * get caught in a loop if the table fills up. The "slots" argument is for when
 * a table is being rebuilt. Set it to NULL to add entries to the same table.
 * Returns true when we're getting rid of a ghost.
 */

static bool tableUnsafeAdd(
                            tableHash *table,
                            tableSlot *slots,
                            cInt new_len,
                            cByte *key,
                            cByte *val
                          )
{
    tableSlot *target;
    cInt target_len;
    cInt search_idx;

    if (slots)
    {
        target = slots;
        target_len = new_len;
    }
    else
    {
        target = table->slots;
        target_len = table->len;
    }

    search_idx = hash32(key, table->key_len) % target_len;

    for (;;)
    {
        if (
            !target[search_idx].used ||
            memcmp(target[search_idx].key, key, table->key_len) == 0
           )
        {
            break;
        }
        else if (++search_idx == target_len)
        {
            search_idx = 0;
        }
    }

    tableSlot *slot = target + search_idx;

    memcpy(slot->key, key, table->key_len);
    memcpy(slot->val, val, table->val_len);
    slot->used = 1;

    if (slot->used_before)
    {
        return true;
    }

    slot->used_before = 1;
    return false;
}

// Transfers all the contents of the old table into a new one.

static void tableRebuild(tableHash *table, tableSlot *new_slots, cInt new_len)
{
    for (cInt i = 0; i < table->len; ++i)
    {
        tableSlot *slot = table->slots + i;

        if (slot->used)
        {
            tableUnsafeAdd(
                            table,
                            new_slots,
                            new_len,
                            slot->key,
                            slot->val
                          );
        }
    }
}

void tableAdd(
                tableHash *table,
                cByte *key,
                cByte *val,
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

        tableRebuild(table, new_slots, new_len);

        free(table->slots);

        table->slots = new_slots;
        table->num_ghosts = 0;
        table->len = new_len;
    }

    if (tableUnsafeAdd(table, NULL, 0, key, val))
    {
        --table->num_ghosts;
    }
    ++table->num;
}

static tableSlot *tablePosLookup(tableHash *table, cByte *key)
{
    cInt table_idx = hash32(key, table->key_len) % table->len;
    cInt search_idx = table_idx;

    do
    {
        tableSlot *slot = table->slots + search_idx++;

        if (!slot->used_before)
        {
            return NULL;
        }
        else if (slot->used && memcmp(slot->key, key, table->key_len) == 0)
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

cByte *tableLookup(tableHash *table, cByte *key)
{
    tableSlot *slot = tablePosLookup(table, key);

    if (slot)
    {
        return &slot->val[0];
    }

    return NULL;
}

void tableDel(tableHash *table, cByte *key, errorCode *error)
{
    tableSlot *slot = tablePosLookup(table, key);

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

            tableRebuild(table, new_slots, table->len);

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
