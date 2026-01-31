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
const GRFRect CELL_MINE = {.x = 50, .y = 403, .w = 48, .h = 48};
const GRFRect CELL_MINE_OTHER = {.x = 246, .y = 403, .w = 48, .h = 48};
const GRFRect CELL_CLOSED = {.x = 99, .y = 452, .w = 48, .h = 48};
const GRFRect CELL_CLOSED_DOWN = {.x = 148, .y = 403, .w = 48, .h = 48};
const GRFRect CELL_FLAG = {.x = 1, .y = 403, .w = 48, .h = 48};
const GRFRect CELL_MARK = {.x = 246, .y = 452, .w = 48, .h = 48};
const GRFRect CELL_MARK_DOWN = {.x = 50, .y = 354, .w = 48, .h = 48};

const GRFRect DIFFICULTY_EASY[2] = {
    {.x = 1, .y = 285, .w = 120, .h = 58},
    {.x = 243, .y = 167, .w = 120, .h = 58},
};
const GRFRect DIFFICULTY_EASY_ACTIVE[2] = {
    {.x = 1, .y = 226, .w = 120, .h = 58},
    {.x = 1, .y = 167, .w = 120, .h = 58},
};
const GRFRect DIFFICULTY_MEDIUM[2] = {
    {.x = 1, .y = 108, .w = 120, .h = 58},
    {.x = 220, .y = 344, .w = 120, .h = 58},
};
const GRFRect DIFFICULTY_MEDIUM_ACTIVE[2] = {
    {.x = 122, .y = 226, .w = 120, .h = 58},
    {.x = 99, .y = 344, .w = 120, .h = 58},
};
const GRFRect DIFFICULTY_HARD[2] = {
    {.x = 243, .y = 226, .w = 120, .h = 58},
    {.x = 243, .y = 285, .w = 120, .h = 58},
};
const GRFRect DIFFICULTY_HARD_ACTIVE[2] = {
    {.x = 122, .y = 167, .w = 120, .h = 58},
    {.x = 122, .y = 285, .w = 120, .h = 58},
};

const GRFRect SMILE_NORMAL[2] = {
    {.x = 1, .y = 25, .w = 82, .h = 82},
    {.x = 167, .y = 1, .w = 82, .h = 82},
};
const GRFRect SMILE_DEAD[2] = {
    {.x = 122, .y = 84, .w = 82, .h = 82},
    {.x = 250, .y = 1, .w = 82, .h = 82},
};
const GRFRect SMILE_WIN[2] = {
    {.x = 205, .y = 84, .w = 82, .h = 82},
    {.x = 288, .y = 84, .w = 82, .h = 82},
};
const GRFRect SMILE_OPEN = {.x = 84, .y = 1, .w = 82, .h = 82};

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
const GRFRect COUNTER_MINE_ICON = {.x = 168, .y = 501, .w = 36, .h = 36};
const GRFRect COUNTER_TIME_ICON = {.x = 79, .y = 501, .w = 36, .h = 36};