# This Makefile can be used with GNU Make or BSD Make

LIB=libgemss128_avx2.a

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,${SOURCES})
HEADERS = *.h

CFLAGS=-O3 -std=c11 -march=native -Wall -Wconversion -Wextra -Wpedantic -Wvla -std=c99 -I../../../common $(EXTRAFLAGS)

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
