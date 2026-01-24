#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>
#include <stdbool.h>

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
bool field_coord(int screen_x, int screen_y, int* field_x, int* field_y);
bool field_is_open(int x, int y);
bool field_is_closed(int x, int y);
void field_open(int x, int y);
void field_mark(int x, int y);

#endif