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

link : $(OBJECTS)
	$(LD) -o $(EXENAME) *.o $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o *.exe $(EXENAME)
