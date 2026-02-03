#include "ui.h"

bool btnIsInside(Button* button, int x, int y) {
    return
        x >= button->x &&
        x <= button->x + button->width &&
        y >= button->y &&
        y <= button->y + button->height;
}

void btnDraw(Button* button) {
    atlas_draw(button->x, button->y, button->face.normal);
}

void btnDrawPressed(Button* button) {
    atlas_draw(button->x, button->y, button->face.pressed);
}

void btnDrawCustom(Button* button, const GRFRect* image) {
    atlas_draw(button->x, button->y, image);
}