EXENAME = idontknow
CC = gcc
LD = gcc
CFLAGS = -std=c99 -Wall -Werror
LDFLAGS = -lm

OPTIMIZE = -O2 -march=native -s
DEBUG = -O0 -g
PROFILE = -pg

OBJECTS = $(shell find . -name "*.c" | sed "s/\.c/.o/g")
INCLUDE = -I. -IdStruct -Imeat -Imeat/loop -Irng

CFLAGS += $(SWITCHES) $(INCLUDE)

ifdef debug
	CFLAGS += $(DEBUG)
else
	CFLAGS += $(OPTIMIZE)
endif

ifdef profile
	CFLAGS += $(PROFILE)
endif

ifdef asm
	CFLAGS += -S
endif

link : $(OBJECTS)
	$(LD) -o $(EXENAME) $^ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f *.exe $(EXENAME) $(OBJECTS)
