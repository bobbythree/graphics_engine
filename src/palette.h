#ifndef PALETTE_H
#define PALETTE_H

#include <stdint.h>

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

extern const uint32_t palette[COLOR_COUNT];

#endif
