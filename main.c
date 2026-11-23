#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdio.h>

#define WIDTH 160
#define HEIGHT 168
#define SCALE 4

// frame buffer
uint32_t framebuffer[HEIGHT][WIDTH];

// EGA color palette
typedef enum {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  LIGHT_GRAY,
  DARK_GRAY,
  LIGHT_BLUE,
  LIGHT_GREEN,
  LIGHT_CYAN,
  LIGHT_RED,
  LIGHT_MAGENTA,
  YELLOW,
  WHITE,
  COLOR_COUNT
} EGAColor;

const uint32_t palette[COLOR_COUNT] = {
    [BLACK] = 0xFF000000,       [BLUE] = 0xFF0000AA,
    [GREEN] = 0xFF00AA00,       [CYAN] = 0xFF00AAAA,
    [RED] = 0xFFAA0000,         [MAGENTA] = 0xFFAA00AA,
    [BROWN] = 0xFFAA5500,       [LIGHT_GRAY] = 0xFFAAAAAA,
    [DARK_GRAY] = 0xFF555555,   [LIGHT_BLUE] = 0xFF5555FF,
    [LIGHT_GREEN] = 0xFF55FF55, [LIGHT_CYAN] = 0xFF55FFFF,
    [LIGHT_RED] = 0xFFFF5555,   [LIGHT_MAGENTA] = 0xFFFF55FF,
    [YELLOW] = 0xFFFFFF55,      [WHITE] = 0xFFFFFFFF};

// draw pixel at coordinate x, y
void putPixel(int x, int y, EGAColor color) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }

  if (color < 0 || color >= COLOR_COUNT) {
    return;
  }

  framebuffer[y][x] = palette[color];
}

// fill entire framebuffer with one color
void clearFrameBuffer(EGAColor color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      putPixel(x, y, color);
    }
  }
}

// drawing primitives
void drawHorizontalLine(int x1, int x2, int y, EGAColor color) {
  if (x1 > x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }

  for (int x = x1; x <= x2; x++) {
    putPixel(x, y, color);
  }
}

void drawVerticalLine(int y1, int y2, int x, EGAColor color) {
  if (y1 > y2) {
    int temp = y1;
    y1 = y2;
    y2 = temp;
  }

  for (int y = y1; y <= y2; y++) {
    putPixel(x, y, color);
  }
}

// main
int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    return 1;
  }

  // create window
  SDL_Window *window =
      SDL_CreateWindow("AGI Graphics Engine", WIDTH * SCALE, HEIGHT * SCALE, 0);

  if (window == NULL) {
    fprintf(stderr, "Window error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  if (renderer == NULL) {
    fprintf(stderr, "Renderer error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // create texture
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  if (texture == NULL) {
    fprintf(stderr, "Texture error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // transfer pixels to texture
  clearFrameBuffer(BLUE);
  drawHorizontalLine(10, 150, 80, WHITE);
  drawVerticalLine(20, 120, 50, WHITE);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));

  // main loop
  bool running = true;
  SDL_Event event;
  while (running) {
    // process all pending events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    // render
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  // tear down
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
