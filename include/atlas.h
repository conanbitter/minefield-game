#ifndef ATLAS_H
#define ATLAS_H

#include "grf.h"

const GRFRect CELL_DIGITS[9];
const GRFRect CELL_MINE;
const GRFRect CELL_CLOSED;
const GRFRect CELL_CLOSED_DOWN;
const GRFRect CELL_FLAG;
const GRFRect CELL_MARK;

const GRFRect DIFFICULTY_UP[3];
const GRFRect DIFFICULTY_DOWN[3];

const GRFRect SMILE_NORMAL;
const GRFRect SMILE_NORMAL_DOWN;
const GRFRect SMILE_OPEN;
const GRFRect SMILE_DEAD;
const GRFRect SMILE_DEAD_DOWN;

const GRFRect COUNTER_DIGITS[10];
const GRFRect COUNTER_ICON;

void atlas_init();
void atlas_draw(int x, int y, const GRFRect* rect);
void atlas_free();

#endif