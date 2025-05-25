# Makefile
CC=gcc
CFLAGS=$(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs) -lmingw32
SRC=main.c
OUT=rpg.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)

fclean: clean

.PHONY: all run clean fclean