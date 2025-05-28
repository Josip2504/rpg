# Makefile
CC=g++
CFLAGS=$(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image -lmingw32
SRC= src/*.cpp
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