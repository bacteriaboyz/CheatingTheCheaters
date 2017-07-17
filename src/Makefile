EXENAME = idontknow
CC = gcc
LD = gcc
CFLAGS = -std=c99 -Wall -Werror -Wno-switch -Wno-format-truncation
LDFLAGS = -lm

OPTIMIZE = -O2 -march=native
DEBUG = -O0 -g
PROFILE = -pg

OBJECTS = $(shell find . -name "*.c" | sed "s/\.c/.o/g") ../jsmn/jsmn.o
INCLUDE = $(shell find . -type d | sed "s/^/-I/;s/\n/ /") -I../jsmn

CFLAGS += $(SWITCHES) -DJSMN_PARENT_LINKS $(INCLUDE)

ifdef debug
	CFLAGS += $(DEBUG)
else
	CFLAGS += $(OPTIMIZE)
	LDFLAGS += -s
endif

ifdef profile
	CFLAGS += $(PROFILE)
endif

$(EXENAME) : $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f *.exe $(EXENAME) $(OBJECTS)
