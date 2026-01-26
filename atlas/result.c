const GRFRect CELL_DIGITS[9] = {
    {.x = 250, .y = 173, .w = 48, .h = 48},
    {.x = 299, .y = 173, .w = 48, .h = 48},
    {.x = 50, .y = 7, .w = 48, .h = 48},
    {.x = 314, .y = 124, .w = 48, .h = 48},
    {.x = 216, .y = 90, .w = 48, .h = 48},
    {.x = 333, .y = 339, .w = 48, .h = 48},
    {.x = 265, .y = 75, .w = 48, .h = 48},
    {.x = 99, .y = 7, .w = 48, .h = 48},
    {.x = 1, .y = 7, .w = 48, .h = 48},
};
const GRFRect CELL_MINE = {.x = 167, .y = 41, .w = 48, .h = 48};
const GRFRect CELL_MINE_OTHER = {.x = 265, .y = 124, .w = 48, .h = 48};
const GRFRect CELL_CLOSED = {.x = 167, .y = 90, .w = 48, .h = 48};
const GRFRect CELL_CLOSED_DOWN = {.x = 216, .y = 41, .w = 48, .h = 48};
const GRFRect CELL_FLAG = {.x = 333, .y = 241, .w = 48, .h = 48};
const GRFRect CELL_MARK = {.x = 333, .y = 290, .w = 48, .h = 48};
const GRFRect CELL_MARK_DOWN = {.x = 314, .y = 75, .w = 48, .h = 48};

const GRFRect DIFFICULTY_EASY[2] = {
    {.x = 84, .y = 222, .w = 82, .h = 82},
    {.x = 250, .y = 222, .w = 82, .h = 82},
};
const GRFRect DIFFICULTY_MEDIUM[2] = {
    {.x = 167, .y = 139, .w = 82, .h = 82},
    {.x = 1, .y = 222, .w = 82, .h = 82},
};
const GRFRect DIFFICULTY_HARD[2] = {
    {.x = 250, .y = 305, .w = 82, .h = 82},
    {.x = 167, .y = 305, .w = 82, .h = 82},
};

const GRFRect SMILE_NORMAL[2] = {
    {.x = 1, .y = 56, .w = 82, .h = 82},
    {.x = 167, .y = 222, .w = 82, .h = 82},
};
const GRFRect SMILE_DEAD[2] = {
    {.x = 1, .y = 305, .w = 82, .h = 82},
    {.x = 84, .y = 56, .w = 82, .h = 82},
};
const GRFRect SMILE_WIN[2] = {
    {.x = 84, .y = 305, .w = 82, .h = 82},
    {.x = 1, .y = 139, .w = 82, .h = 82},
};
const GRFRect SMILE_OPEN = {.x = 84, .y = 139, .w = 82, .h = 82};

const GRFRect COUNTER_DIGITS[10] = {
    {.x = 252, .y = 1, .w = 25, .h = 36},
    {.x = 148, .y = 4, .w = 25, .h = 36},
    {.x = 304, .y = 1, .w = 25, .h = 36},
    {.x = 200, .y = 4, .w = 25, .h = 36},
    {.x = 339, .y = 38, .w = 25, .h = 36},
    {.x = 278, .y = 1, .w = 25, .h = 36},
    {.x = 174, .y = 4, .w = 25, .h = 36},
    {.x = 330, .y = 1, .w = 25, .h = 36},
    {.x = 226, .y = 4, .w = 25, .h = 36},
    {.x = 348, .y = 204, .w = 25, .h = 36},
};
const GRFRect COUNTER_MINE_ICON = {.x = 302, .y = 38, .w = 36, .h = 36};
const GRFRect COUNTER_TIME_ICON = {.x = 265, .y = 38, .w = 36, .h = 36};