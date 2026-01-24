#ifndef ATLAS_H
#define ATLAS_H

#include "grf.h"

void atlas_init();
void atlas_draw(int x, int y, const GRFRect* rect);
void atlas_free();

#endif