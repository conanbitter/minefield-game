#include "field.h"
#include "atlas.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CELL_STATUS_CLOSED (0)
#define CELL_STATUS_OPENED (1)
#define CELL_STATUS_FLAGGED (2)
#define CELL_STATUS_MARKED (3)

typedef struct FieldCell {
    int mines;
    bool is_mine;
    int status;
} FieldCell;

static FieldCell field[FIELD_MAX_WIDTH * FIELD_MAX_HEIGHT];
static int field_cells[FIELD_MAX_WIDTH * FIELD_MAX_HEIGHT];

int field_width;
int field_height;

static FieldCell* get_cell(int x, int y) {
    return &field[x + y * field_width];
}

void field_init(int width, int height, int mines) {
    field_width = width;
    field_height = height;
    for (int i = 0;i < width * height;i++) {
        field[i].is_mine = false;
        field[i].mines = 0;
        field[i].status = CELL_STATUS_OPENED;
    }
    srand(time(NULL));
}

void field_populate(int mines, int exclude_x, int exclude_y) {
    int field_size = field_width * field_height;
    int ind = 0;
    for (int y = 0;y < field_height;y++) {
        for (int x = 0;x < field_width;x++) {
            if (abs(exclude_x - x) <= 1 && abs(exclude_y - y) <= 1) continue;
            field_cells[ind++] = x + y * field_width;
        }
    }
    for (int i = 0;i < mines;i++) {
        int other = rand() % ind;
        int temp = field_cells[i];
        field_cells[i] = field_cells[other];
        field_cells[other] = temp;
    }
    for (int i = 0;i < mines;i++) {
        field[field_cells[i]].is_mine = true;
    }
    for (int y = 0;y < field_height;y++) {
        for (int x = 0;x < field_width;x++) {
            FieldCell* cur = get_cell(x, y);
            if (cur->is_mine) continue;
            if (x > 0 && y > 0 && get_cell(x - 1, y - 1)->is_mine) cur->mines++;
            if (y > 0 && get_cell(x, y - 1)->is_mine) cur->mines++;
            if (x < field_width - 1 && y > 0 && get_cell(x + 1, y - 1)->is_mine) cur->mines++;
            if (x < field_width - 1 && get_cell(x + 1, y)->is_mine) cur->mines++;
            if (x < field_width - 1 && y < field_height - 1 && get_cell(x + 1, y + 1)->is_mine) cur->mines++;
            if (y < field_height - 1 && get_cell(x, y + 1)->is_mine) cur->mines++;
            if (x > 0 && y < field_height - 1 && get_cell(x - 1, y + 1)->is_mine) cur->mines++;
            if (x > 0 && get_cell(x - 1, y)->is_mine) cur->mines++;
        }
    }
}

void field_draw_cell(int x, int y) {
    FieldCell* cell = get_cell(x, y);
    int cell_x = x * FIELD_CELL_SIZE + FIELD_OFFSET_X;
    int cell_y = y * FIELD_CELL_SIZE + FIELD_OFFSET_Y;
    switch (cell->status)
    {
    case CELL_STATUS_CLOSED:
        atlas_draw(cell_x, cell_y, &CELL_CLOSED);
        break;
    case CELL_STATUS_FLAGGED:
        atlas_draw(cell_x, cell_y, &CELL_FLAG);
        break;
    case CELL_STATUS_MARKED:
        atlas_draw(cell_x, cell_y, &CELL_MARK);
        break;
    case CELL_STATUS_OPENED:
        if (cell->is_mine) {
            atlas_draw(cell_x, cell_y, &CELL_MINE);
        } else {
            atlas_draw(cell_x, cell_y, &CELL_DIGITS[cell->mines]);
        }
        break;

    default:
        break;
    }
}