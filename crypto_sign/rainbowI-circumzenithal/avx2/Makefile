# This Makefile can be used with GNU Make or BSD Make

LIB=librainbowI-circumzenithal_avx2.a

HEADERS = *.h
CFILES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,${CFILES}) 


CFLAGS=-O3 -Wall -Wconversion -march=native -Wextra -Wpedantic -Wvla -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common $(EXTRAFLAGS)

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
