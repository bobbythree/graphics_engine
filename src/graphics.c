#include "graphics.h"
#include "palette.h"

// frame buffer
uint32_t framebuffer[HEIGHT][WIDTH];

// draw pixel at coordinate x, y
void put_pixel(int x, int y, ega_color color) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }

  if (color < 0 || color >= COLOR_COUNT) {
    return;
  }

  framebuffer[y][x] = palette[color];
}

// fill entire framebuffer with one color
void clear_frame_buffer(ega_color color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      put_pixel(x, y, color);
    }
  }
}

// drawing primitives
void draw_horizontal_line(int x1, int x2, int y, ega_color color) {
  if (x1 > x2) { // swap coords and draw opposite way
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }

  for (int x = x1; x <= x2; x++) {
    put_pixel(x, y, color);
  }
}

void draw_vertical_line(int y1, int y2, int x, ega_color color) {
  if (y1 > y2) {
    int temp = y1;
    y1 = y2;
    y2 = temp;
  }

  for (int y = y1; y <= y2; y++) {
    put_pixel(x, y, color);
  }
}

void draw_diagonal_line(int x1, int y1, int x2, int y2, ega_color color) {

  int y_step;
  if (y1 > y2) {
    y_step = -1;
  } else {
    y_step = 1;
  }

  for (int x = x1, y = y1; x <= x2; x++, y += y_step) {
    put_pixel(x, y, color);
  }
}
