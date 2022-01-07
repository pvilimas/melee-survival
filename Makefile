CFLAGS = -std=c11 -Wall -Wextra -g -lm -lSDL2 -o main
SRC = main.c game.c graphics.c

all: clean build run

main: $(SRC)
	gcc $(CFLAGS) $^ -o $@

build: main

run: main
	./main

clean:
	rm -f main