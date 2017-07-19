EXENAME = idontknow
CC = gcc
LD = gcc
CFLAGS = -std=c99 -Wall -Werror -Wno-switch -Wno-format-truncation
LDFLAGS =

OPTIMIZE = -O2 -march=native
DEBUG = -O0 -g
PROFILE = -pg
STRIP = -s

OBJECTS = $(shell find . -name "*.c" | sed "s/\.c/.o/g") ../jsmn/jsmn.o
INCLUDE = $(shell find . -type d | sed "s/^/-I/;s/\n/ /") -I../jsmn

LIBS = -lm

CFLAGS += $(CS) -DJSMN_PARENT_LINKS $(INCLUDE)
LDFLAGS += $(LS) $(LIBS)

ifdef debug
	CFLAGS += $(DEBUG)
else
	CFLAGS += $(OPTIMIZE)
	LDFLAGS += $(STRIP)
endif

ifdef profile
	CFLAGS += $(PROFILE)
	LDFLAGS += $(PROFILE)
endif

$(EXENAME) : $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f *.exe $(EXENAME) $(OBJECTS)
