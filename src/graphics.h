#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "palette.h"
#include <stdint.h>

#define WIDTH 160
#define HEIGHT 168

extern uint32_t framebuffer[HEIGHT][WIDTH];

void putPixel(int x, int y, EGAColor color);
void clearFrameBuffer(EGAColor color);
void drawHorizontalLine(int x1, int x2, int y, EGAColor color);
void drawVerticalLine(int y1, int y2, int x, EGAColor color);
void drawDiagonalLine(int x1, int y1, int x2, int y2, EGAColor color);

#endif
