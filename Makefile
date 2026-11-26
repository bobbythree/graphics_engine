CC = clang
CFLAGS = -g -O0 -Wall -Wextra -fsanitize=address,undefined
SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
SDL_LIBS = $(shell pkg-config --libs sdl3)

TARGET = graphics_engine
SRC = src/main.c src/palette.c src/graphics.c

.PHONY: all run run-wayland clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(SRC) -o $(TARGET) $(SDL_LIBS)

run: $(TARGET)
	SDL_VIDEO_DRIVER=x11 ./$(TARGET)

run-wayland: $(TARGET)
	SDL_VIDEO_DRIVER=wayland ./$(TARGET)

clean:
	rm -f $(TARGET)
