#include "graphics.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdio.h>

#define SCALE 4

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
  clear_frame_buffer(BLUE);
  // draw_horizontal_line(10, 150, 80, WHITE);
  // draw_vertical_line(20, 120, 50, WHITE);
  // draw_diagonal_line(10, 10, 50, 50, WHITE);
  draw_line(80, 84, 140, 104, WHITE);
  draw_line(80, 84, 100, 144, WHITE);
  draw_line(80, 84, 60, 144, WHITE);
  draw_line(80, 84, 20, 104, WHITE);
  draw_line(80, 84, 20, 64, WHITE);
  draw_line(80, 84, 60, 24, WHITE);
  draw_line(80, 84, 100, 24, WHITE);
  draw_line(80, 84, 140, 64, WHITE);
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
