#include "atlas.h"
#include "grf.h"

static GRFImage atlas;

const GRFRect CELL_DIGITS[9] = {
    {.x = 1, .y = 1, .w = 48, .h = 48},
    {.x = 50, .y = 1, .w = 48, .h = 48},
    {.x = 99, .y = 1, .w = 48, .h = 48},
    {.x = 148, .y = 1, .w = 48, .h = 48},
    {.x = 197, .y = 1, .w = 48, .h = 48},
    {.x = 246, .y = 1, .w = 48, .h = 48},
    {.x = 295, .y = 1, .w = 48, .h = 48},
    {.x = 344, .y = 1, .w = 48, .h = 48},
    {.x = 393, .y = 1, .w = 48, .h = 48},
};

const GRFRect CELL_MINE = { .x = 442, .y = 1, .w = 48, .h = 48 };
const GRFRect CELL_CLOSED = { .x = 406, .y = 133, .w = 48, .h = 48 };
const GRFRect CELL_CLOSED_DOWN = { .x = 455, .y = 133, .w = 48, .h = 48 };
const GRFRect CELL_FLAG = { .x = 406, .y = 182, .w = 48, .h = 48 };
const GRFRect CELL_MARK = { .x = 455, .y = 182, .w = 48, .h = 48 };

const GRFRect DIFFICULTY_UP[3] = {
    {.x = 1, .y = 50, .w = 82, .h = 82},
    {.x = 167, .y = 50, .w = 82, .h = 82},
    {.x = 333, .y = 50, .w = 82, .h = 82},
};

const GRFRect DIFFICULTY_DOWN[3] = {
    {.x = 84, .y = 50, .w = 82, .h = 82},
    {.x = 250, .y = 50, .w = 82, .h = 82},
    {.x = 416, .y = 50, .w = 82, .h = 82},
};

const GRFRect SMILE_NORMAL = { .x = 1, .y = 133, .w = 80, .h = 80 };
const GRFRect SMILE_NORMAL_DOWN = { .x = 82, .y = 133, .w = 80, .h = 80 };
const GRFRect SMILE_OPEN = { .x = 163, .y = 133, .w = 80, .h = 80 };
const GRFRect SMILE_DEAD = { .x = 244, .y = 133, .w = 80, .h = 80 };
const GRFRect SMILE_DEAD_DOWN = { .x = 325, .y = 133, .w = 80, .h = 80 };

const GRFRect COUNTER_DIGITS[10] = {
    {.x = 1, .y = 216, .w = 25, .h = 36},
    {.x = 27, .y = 216, .w = 25, .h = 36},
    {.x = 53, .y = 216, .w = 25, .h = 36},
    {.x = 79, .y = 216, .w = 25, .h = 36},
    {.x = 105, .y = 216, .w = 25, .h = 36},
    {.x = 131, .y = 216, .w = 25, .h = 36},
    {.x = 157, .y = 216, .w = 25, .h = 36},
    {.x = 183, .y = 216, .w = 25, .h = 36},
    {.x = 209, .y = 216, .w = 25, .h = 36},
    {.x = 235, .y = 216, .w = 25, .h = 36},
};
const GRFRect COUNTER_ICON = { .x = 261, .y = 216, .w = 36, .h = 36 };

void atlas_init() {
    atlas = grfLoadImageFromRes(L"bmAtlas");
}

void atlas_draw(int x, int y, const GRFRect* rect) {
    grfDrawImage(atlas, x, y, rect);
}

void atlas_free() {
    grfFreeImage(atlas);
}