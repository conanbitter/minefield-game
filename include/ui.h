#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include "atlas.h"

typedef struct Button
{
    int x;
    int y;
    int width;
    int height;
    ButtonFace face;
    int id;
} Button;

bool btnIsInside(Button* button, int x, int y);
void btnDraw(Button* button);
void btnDrawPressed(Button* button);
void btnDrawCustom(Button* button, const GRFRect* image);

#endif