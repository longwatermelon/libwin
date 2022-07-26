CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall
LIBS=-lX11

AR=ar
ARFLAGS=rc

SRC=$(wildcard src/*.c)
OBJS=$(addprefix obj/, $(SRC:.c=.o))

.PHONY: dirs

all: dirs lib target

target: lib example.c
	$(CC) $(CFLAGS) -Isrc example.c -Llib -lwin $(LIBS)

lib: $(OBJS)
	$(AR) $(ARFLAGS) lib/libwin.a $^

obj/src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p obj/src lib

clean:
	-rm -rf obj lib a.out

