#include "graphics.h"
#include "palette.h"
#include <stdbool.h>
#include <stdlib.h>

// stores the color value of every pixel
uint32_t framebuffer[HEIGHT][WIDTH];

// draw a single pixel at the given coordinates
void put_pixel(int x, int y, ega_color color) {
  // ignore coordinates outside the framebuffer
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return;
  }

  // ignore invalid palette colors
  if (color < 0 || color >= COLOR_COUNT) {
    return;
  }

  framebuffer[y][x] = palette[color];
}

// fill the entire framebuffer with one color
void clear_frame_buffer(ega_color color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      put_pixel(x, y, color);
    }
  }
}

// draw a horizontal line at a fixed y coordinate
void draw_horizontal_line(int x1, int x2, int y, ega_color color) {
  // swap endpoints if x1 is greater than x2
  if (x1 > x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
  }

  for (int x = x1; x <= x2; x++) {
    put_pixel(x, y, color);
  }
}

// draw a vertical line at a fixed x coordinate
void draw_vertical_line(int y1, int y2, int x, ega_color color) {
  // swap endpoints if y1 is greater than y2
  if (y1 > y2) {
    int temp = y1;
    y1 = y2;
    y2 = temp;
  }

  for (int y = y1; y <= y2; y++) {
    put_pixel(x, y, color);
  }
}

// draw a 45-degree diagonal line from left to right
void draw_diagonal_line(int x1, int y1, int x2, int y2, ega_color color) {

  // move up or down depending on the endpoint
  int y_step;
  if (y1 > y2) {
    y_step = -1;
  } else {
    y_step = 1;
  }

  // move one pixel horizontally and vertically each iteration
  for (int x = x1, y = y1; x <= x2; x++, y += y_step) {
    put_pixel(x, y, color);
  }
}

// draw a line using Bresenham's algorithm
void draw_line(int x1, int y1, int x2, int y2, ega_color color) {
  // determine whether to move up or down
  int y_step;
  if (y1 > y2) {
    y_step = -1;
  } else {
    y_step = 1;
  }

  // determine whether to move left or right
  int x_step;
  if (x1 > x2) {
    x_step = -1;
  } else {
    x_step = 1;
  }

  // calculate the total distance to travel along each axis
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);

  // initialize the error using the difference between axis distances
  int error_acc = (dx - dy);

  // start drawing at the first endpoint
  int x = x1;
  int y = y1;

  while (true) {
    put_pixel(x, y, color);

    // exit after drawing the final pixel
    if (x == x2 && y == y2) {
      break;
    }

    // double the error to avoid fractional stepping thresholds
    int e2 = 2 * error_acc;

    // move horizontally if the error is above the horizontal threshold
    if (e2 > -dy) {
      error_acc -= dy;
      x += x_step;
    }

    // move vertically if the error is below the vertical threshold
    if (e2 < dx) {
      error_acc += dx;
      y += y_step;
    }
  }
}
