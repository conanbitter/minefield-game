#include "field.h"
#include "atlas.h"
#include <string.h>
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
    bool visited;
    int x;
    int y;
    int neighbours[8];
} FieldCell;

static FieldCell field[FIELD_MAX_WIDTH * FIELD_MAX_HEIGHT];
static int field_cells[FIELD_MAX_WIDTH * FIELD_MAX_HEIGHT];
static int cell_count;
static bool first_mines = true;

int field_width;
int field_height;
int field_size;

static FieldCell* get_cell(int x, int y) {
    return &field[x + y * field_width];
}

void fieldInit(int width, int height, int mines) {
    field_width = width;
    field_height = height;
    field_size = field_width * field_height;
    for (int y = 0;y < field_height;y++) {
        for (int x = 0;x < field_width;x++) {
            FieldCell* cur = get_cell(x, y);
            cur->is_mine = false;
            cur->status = CELL_STATUS_CLOSED;
            cur->mines = 0;
            cur->x = x;
            cur->y = y;

            int neighbour_count = 0;
            if (x > 0 && y > 0) cur->neighbours[neighbour_count++] = x - 1 + (y - 1) * field_width;
            if (y > 0) cur->neighbours[neighbour_count++] = x + (y - 1) * field_width;
            if (x < field_width - 1 && y > 0) cur->neighbours[neighbour_count++] = x + 1 + (y - 1) * field_width;
            if (x < field_width - 1) cur->neighbours[neighbour_count++] = x + 1 + y * field_width;
            if (x < field_width - 1 && y < field_height - 1) cur->neighbours[neighbour_count++] = x + 1 + (y + 1) * field_width;
            if (y < field_height - 1) cur->neighbours[neighbour_count++] = x + (y + 1) * field_width;
            if (x > 0 && y < field_height - 1) cur->neighbours[neighbour_count++] = x - 1 + (y + 1) * field_width;
            if (x > 0) cur->neighbours[neighbour_count++] = x - 1 + y * field_width;
            for (int i = neighbour_count;i < 8;i++) cur->neighbours[i] = -1;
        }
    }

    srand(time(NULL));
}

void fieldPopulate(int mines, int exclude_cell) {
    int ind = 0;
    int exclude_x = field[exclude_cell].x;
    int exclude_y = field[exclude_cell].y;
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
    for (int i = 0;i < field_size;i++) {
        FieldCell* cur = &field[i];
        if (cur->is_mine) continue;
        for (int j = 0;j < 8;j++) {
            if (cur->neighbours[j] < 0) break;
            if (field[cur->neighbours[j]].is_mine) cur->mines++;
        }
    }
}

static drawCell(FieldCell* cell, int x, int y) {
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
            if (first_mines) {
                atlas_draw(cell_x, cell_y, &CELL_MINE);
            } else {
                atlas_draw(cell_x, cell_y, &CELL_MINE_OTHER);
            }
        } else {
            atlas_draw(cell_x, cell_y, &CELL_DIGITS[cell->mines]);
        }
        break;

    default:
        break;
    }
}

void fieldDrawCellXY(int x, int y) {
    FieldCell* cell = get_cell(x, y);
    drawCell(cell, x, y);
}

void fieldDrawCellInd(int index) {
    FieldCell* cell = &field[index];
    drawCell(cell, cell->x, cell->y);
}

void fieldDrawCell(FieldCell* cell) {
    drawCell(cell, cell->x, cell->y);
}

void fieldDrawCellCustomXY(int x, int y, GRFRect* image) {
    atlas_draw(
        x * FIELD_CELL_SIZE + FIELD_OFFSET_X,
        y * FIELD_CELL_SIZE + FIELD_OFFSET_Y,
        image);
}

void fieldDrawCellCustomInd(int index, const  GRFRect* image) {
    atlas_draw(
        field[index].x * FIELD_CELL_SIZE + FIELD_OFFSET_X,
        field[index].y * FIELD_CELL_SIZE + FIELD_OFFSET_Y,
        image);
}

int fieldCellByScreenXY(int screen_x, int screen_y) {
    if (screen_x < FIELD_OFFSET_X ||
        screen_x >= FIELD_OFFSET_X + field_width * FIELD_CELL_SIZE ||
        screen_y < FIELD_OFFSET_Y ||
        screen_y >= FIELD_OFFSET_Y + field_height * FIELD_CELL_SIZE) {
        return -1;
    }
    int field_x = (screen_x - FIELD_OFFSET_X) / FIELD_CELL_SIZE;
    int field_y = (screen_y - FIELD_OFFSET_Y) / FIELD_CELL_SIZE;
    return field_x + field_y * field_width;
}

bool cellIsOpen(int index) {
    return field[index].status == CELL_STATUS_OPENED;
}

bool cellIsClosed(int index) {
    return field[index].status == CELL_STATUS_CLOSED;
}

static addCell(int index) {
    field_cells[cell_count++] = index;
}

static propagate() {
    for (int i = 0;i < field_size;i++) {
        field[i].visited = false;
    }

    while (cell_count > 0) {
        int index = field_cells[cell_count - 1];
        cell_count--;
        FieldCell* cell = &field[index];
        if (cell->visited) continue;
        cell->visited = true;
        cell->status = CELL_STATUS_OPENED;
        fieldDrawCell(cell);
        if (cell->mines == 0) {
            for (int i = 0;i < 8;i++) {
                if (cell->neighbours[i] < 0) break;
                FieldCell* next_cell = &field[cell->neighbours[i]];
                if (next_cell->status == CELL_STATUS_CLOSED && !next_cell->is_mine) {
                    field_cells[cell_count++] = cell->neighbours[i];
                }
            }
        }
    }
}

int fieldOpen(int index) {
    int result = RESULT_NORMAL;
    FieldCell* current = &field[index];
    if (current->status != CELL_STATUS_CLOSED && current->status != CELL_STATUS_MARKED) {
        return result;
    }

    current->status = CELL_STATUS_OPENED;

    grfBeginDraw();
    if (current->is_mine) {
        result = RESULT_LOOSE;
        first_mines = true;
        fieldDrawCell(current);
        first_mines = false;
        for (int i = 0;i < field_size;i++) {
            FieldCell* minecell = &field[i];
            if (minecell->is_mine && minecell->status != CELL_STATUS_OPENED) {
                minecell->status = CELL_STATUS_OPENED;
                fieldDrawCell(minecell);
            }
        }
    } else {
        cell_count = 0;
        addCell(index);
        propagate();
        //field_draw_cell(x, y);
    }

    grfEndDraw();
    return result;
}

void fieldMark(int index) {
    FieldCell* cell = &field[index];
    if (cell->status == CELL_STATUS_CLOSED) {
        cell->status = CELL_STATUS_FLAGGED;
        grfBeginDraw();
        fieldDrawCell(cell);
        grfEndDraw();
    } else if (cell->status == CELL_STATUS_FLAGGED) {
        cell->status = CELL_STATUS_CLOSED;
        grfBeginDraw();
        fieldDrawCell(cell);
        grfEndDraw();
    }
}