#ifndef ATLAS_H
#define ATLAS_H

#include "grf.h"

const GRFRect CELL_DIGITS[9];
const GRFRect CELL_MINE;
const GRFRect CELL_MINE_OTHER;
const GRFRect CELL_CLOSED;
const GRFRect CELL_CLOSED_DOWN;
const GRFRect CELL_FLAG;
const GRFRect CELL_MARK;
const GRFRect CELL_MARK_DOWN;

const GRFRect DIFFICULTY_EASY[2];
const GRFRect DIFFICULTY_MEDIUM[2];
const GRFRect DIFFICULTY_HARD[2];

const GRFRect SMILE_NORMAL[2];
const GRFRect SMILE_DEAD[2];
const GRFRect SMILE_WIN[2];
const GRFRect SMILE_OPEN;

const GRFRect COUNTER_DIGITS[10];
const GRFRect COUNTER_MINE_ICON;
const GRFRect COUNTER_TIME_ICON;

void atlas_init();
void atlas_draw(int x, int y, const GRFRect* rect);
void atlas_free();

#endif