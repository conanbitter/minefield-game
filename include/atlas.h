#ifndef ATLAS_H
#define ATLAS_H

#include "grf.h"

typedef struct ButtonFace {
    const GRFRect* normal;
    const GRFRect* pressed;
} ButtonFace;

const GRFRect CELL_DIGITS[9];
const GRFRect CELL_MINE;
const GRFRect CELL_MINE_OTHER;
const GRFRect CELL_CLOSED;
const GRFRect CELL_CLOSED_DOWN;
const GRFRect CELL_FLAG;
const GRFRect CELL_MARK;
const GRFRect CELL_MARK_DOWN;

const ButtonFace DIFFICULTY_EASY;
const ButtonFace DIFFICULTY_EASY_ACTIVE;
const ButtonFace DIFFICULTY_MEDIUM;
const ButtonFace DIFFICULTY_MEDIUM_ACTIVE;
const ButtonFace DIFFICULTY_HARD;
const ButtonFace DIFFICULTY_HARD_ACTIVE;

const ButtonFace SMILE_NORMAL;
const ButtonFace SMILE_DEAD;
const ButtonFace SMILE_WIN;
const GRFRect SMILE_OPEN;

const GRFRect COUNTER_DIGITS[10];
const GRFRect COUNTER_MINE_ICON;
const GRFRect COUNTER_TIME_ICON;

void atlas_init();
void atlas_draw(int x, int y, const GRFRect* rect);
void atlas_free();

#endif