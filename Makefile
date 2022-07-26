CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall
LIBS=-lX11

SRC=$(wildcard src/*.c)
OBJS=$(addprefix obj/, $(SRC:.c=.o))

.PHONY: dirs

all: dirs target

target: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS)

obj/src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p obj/src

clean:
	-rm -rf obj/ a.out

