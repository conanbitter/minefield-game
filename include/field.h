#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>

#define FIELD_CELL_SIZE (48)
#define FIELD_MAX_WIDTH (30)
#define FIELD_MAX_HEIGHT (16)

void field_init(int width, int height, int mines);
void field_draw(int offset_x, int offset_y);

#endif