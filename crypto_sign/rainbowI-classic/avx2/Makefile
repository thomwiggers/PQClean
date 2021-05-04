# This Makefile can be used with GNU Make or BSD Make

LIB=librainbowI-classic_avx2.a

HEADERS = *.h
CFILES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,${CFILES})

CFLAGS=-O3 -mavx2 -Wall -Wconversion -Wextra -Wpedantic -Wvla -Wno-error -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common $(EXTRAFLAGS)

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
