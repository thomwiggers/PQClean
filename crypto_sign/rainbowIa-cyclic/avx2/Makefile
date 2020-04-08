# This Makefile can be used with GNU Make or BSD Make

LIB=librainbowIa-cyclic_clean.a

HEADERS = $(wildcard *.h)
OBJECTS = $(subst .c,.o,$(wildcard *.c))

CFLAGS=-O3 -std=c11 -mavx2 -Wall -Wextra -Wpedantic -I../../../common $(EXTRAFLAGS)

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
