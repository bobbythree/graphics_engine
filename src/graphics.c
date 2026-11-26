#include "graphics.h"

// frame buffer
uint32_t framebuffer[HEIGHT][WIDTH];

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
  if (x1 > x2) { // swap coords and draw opposite way
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
