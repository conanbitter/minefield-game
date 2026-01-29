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
void fieldPopulate(int mines, int exclude_cell);
void fieldDrawCellXY(int x, int y);
void fieldDrawCellInd(int index);
int field_width;
int field_height;
int field_size;
int fieldCellByScreenXY(int screen_x, int screen_y);
bool fieldIsOpen(int index);
bool fieldIsClosed(int index);
int fieldOpen(int index);
void fieldMark(int index);

#endif