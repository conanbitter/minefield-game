#include "atlas.h"
#include "grf.h"

static GRFImage atlas;

const GRFRect CELL_DIGITS[9] = {
    {.x = 148, .y = 452, .w = 48, .h = 48},
    {.x = 197, .y = 403, .w = 48, .h = 48},
    {.x = 197, .y = 452, .w = 48, .h = 48},
    {.x = 1, .y = 354, .w = 48, .h = 48},
    {.x = 99, .y = 403, .w = 48, .h = 48},
    {.x = 50, .y = 452, .w = 48, .h = 48},
    {.x = 295, .y = 403, .w = 48, .h = 48},
    {.x = 295, .y = 452, .w = 48, .h = 48},
    {.x = 1, .y = 452, .w = 48, .h = 48},
};
const GRFRect CELL_MINE = { .x = 50, .y = 403, .w = 48, .h = 48 };
const GRFRect CELL_MINE_OTHER = { .x = 246, .y = 403, .w = 48, .h = 48 };
const GRFRect CELL_CLOSED = { .x = 99, .y = 452, .w = 48, .h = 48 };
const GRFRect CELL_CLOSED_DOWN = { .x = 148, .y = 403, .w = 48, .h = 48 };
const GRFRect CELL_FLAG = { .x = 1, .y = 403, .w = 48, .h = 48 };
const GRFRect CELL_MARK = { .x = 246, .y = 452, .w = 48, .h = 48 };
const GRFRect CELL_MARK_DOWN = { .x = 50, .y = 354, .w = 48, .h = 48 };

static const GRFRect DIFFICULTY_EASY_NORMAL = { .x = 1, .y = 285, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_EASY_PRESSED = { .x = 243, .y = 167, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_EASY = {
    .normal = &DIFFICULTY_EASY_NORMAL,
    .pressed = &DIFFICULTY_EASY_PRESSED
};

static const GRFRect DIFFICULTY_EASY_ACTIVE_NORMAL = { .x = 1, .y = 226, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_EASY_ACTIVE_PRESSED = { .x = 1, .y = 167, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_EASY_ACTIVE = {
    .normal = &DIFFICULTY_EASY_ACTIVE_NORMAL,
    .pressed = &DIFFICULTY_EASY_ACTIVE_PRESSED
};

static const GRFRect DIFFICULTY_MEDIUM_NORMAL = { .x = 1, .y = 108, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_MEDIUM_PRESSED = { .x = 220, .y = 344, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_MEDIUM = {
    .normal = &DIFFICULTY_MEDIUM_NORMAL,
    .pressed = &DIFFICULTY_MEDIUM_PRESSED
};

static const GRFRect DIFFICULTY_MEDIUM_ACTIVE_NORMAL = { .x = 122, .y = 226, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_MEDIUM_ACTIVE_PRESSED = { .x = 99, .y = 344, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_MEDIUM_ACTIVE = {
    .normal = &DIFFICULTY_MEDIUM_ACTIVE_NORMAL,
    .pressed = &DIFFICULTY_MEDIUM_ACTIVE_PRESSED
};

static const GRFRect DIFFICULTY_HARD_NORMAL = { .x = 243, .y = 226, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_HARD_PRESSED = { .x = 243, .y = 285, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_HARD = {
    .normal = &DIFFICULTY_HARD_NORMAL,
    .pressed = &DIFFICULTY_HARD_PRESSED
};

static const GRFRect DIFFICULTY_HARD_ACTIVE_NORMAL = { .x = 122, .y = 167, .w = 120, .h = 58 };
static const GRFRect DIFFICULTY_HARD_ACTIVE_PRESSED = { .x = 122, .y = 285, .w = 120, .h = 58 };
const ButtonFace DIFFICULTY_HARD_ACTIVE = {
    .normal = &DIFFICULTY_HARD_ACTIVE_NORMAL,
    .pressed = &DIFFICULTY_HARD_ACTIVE_PRESSED
};

static const GRFRect SMILE_NORMAL_NORMAL = { .x = 1, .y = 25, .w = 82, .h = 82 };
static const GRFRect SMILE_NORMAL_PRESSED = { .x = 167, .y = 1, .w = 82, .h = 82 };
const ButtonFace SMILE_NORMAL = {
    .normal = &SMILE_NORMAL_NORMAL,
    .pressed = &SMILE_NORMAL_PRESSED
};

static const GRFRect SMILE_DEAD_NORMAL = { .x = 122, .y = 84, .w = 82, .h = 82 };
static const GRFRect SMILE_DEAD_PRESSED = { .x = 250, .y = 1, .w = 82, .h = 82 };
const ButtonFace SMILE_DEAD = {
    .normal = &SMILE_DEAD_NORMAL,
    .pressed = &SMILE_DEAD_PRESSED
};

static const GRFRect SMILE_WIN_NORMAL = { .x = 205, .y = 84, .w = 82, .h = 82 };
static const GRFRect SMILE_WIN_PRESSED = { .x = 288, .y = 84, .w = 82, .h = 82 };
const ButtonFace SMILE_WIN = {
    .normal = &SMILE_WIN_NORMAL,
    .pressed = &SMILE_WIN_PRESSED
};

const GRFRect SMILE_OPEN = { .x = 84, .y = 1, .w = 82, .h = 82 };

const GRFRect COUNTER_DIGITS[10] = {
    {.x = 231, .y = 501, .w = 25, .h = 36},
    {.x = 53, .y = 501, .w = 25, .h = 36},
    {.x = 283, .y = 501, .w = 25, .h = 36},
    {.x = 142, .y = 501, .w = 25, .h = 36},
    {.x = 1, .y = 501, .w = 25, .h = 36},
    {.x = 257, .y = 501, .w = 25, .h = 36},
    {.x = 116, .y = 501, .w = 25, .h = 36},
    {.x = 309, .y = 501, .w = 25, .h = 36},
    {.x = 205, .y = 501, .w = 25, .h = 36},
    {.x = 27, .y = 501, .w = 25, .h = 36},
};
const GRFRect COUNTER_MINE_ICON = { .x = 168, .y = 501, .w = 36, .h = 36 };
const GRFRect COUNTER_TIME_ICON = { .x = 79, .y = 501, .w = 36, .h = 36 };

void atlas_init() {
    atlas = grfLoadImageFromRes(L"bmAtlas");
}

void atlas_draw(int x, int y, const GRFRect* rect) {
    grfDrawImage(atlas, x, y, rect);
}

void atlas_free() {
    grfFreeImage(atlas);
}