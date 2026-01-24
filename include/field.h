#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>

#define FIELD_CELL_SIZE (48)
#define FIELD_MAX_WIDTH (30)
#define FIELD_MAX_HEIGHT (16)

#define FIELD_OFFSET_X (20)
#define FIELD_OFFSET_Y (90)

void field_init(int width, int height, int mines);
void field_populate(int mines, int exclude_x, int exclude_y);
void field_draw_cell(int x, int y);
int field_width;
int field_height;

#endif