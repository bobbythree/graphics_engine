#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "palette.h"
#include <stdint.h>

#define WIDTH 160
#define HEIGHT 168

extern uint32_t framebuffer[HEIGHT][WIDTH];

void put_pixel(int x, int y, ega_color color);
void clear_frame_buffer(ega_color color);
void draw_horizontal_line(int x1, int x2, int y, ega_color color);
void draw_vertical_line(int y1, int y2, int x, ega_color color);
void draw_diagonal_line(int x1, int y1, int x2, int y2, ega_color color);

#endif
