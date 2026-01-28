#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>
#include <stdbool.h>

#define FIELD_CELL_SIZE (48)
#define FIELD_MAX_WIDTH (30)
#define FIELD_MAX_HEIGHT (16)

#define FIELD_OFFSET_X (20)
#define FIELD_OFFSET_Y (90)

#define RESULT_NORMAL (0)
#define RESULT_WIN (1)
#define RESULT_LOOSE (2)

void fieldInit(int width, int height, int mines);
void fieldPopulate(int mines, int exclude_x, int exclude_y);
void fieldDrawCellXY(int x, int y);
int field_width;
int field_height;
bool fieldScreenToXY(int screen_x, int screen_y, int* field_x, int* field_y);
bool fieldIsOpen(int x, int y);
bool fieldIsClosed(int x, int y);
int fieldOpen(int x, int y);
void fieldMark(int x, int y);

#endif