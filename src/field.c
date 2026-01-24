#include "field.h"
#include <string.h>

static uint8_t field[FIELD_MAX_WIDTH * FIELD_MAX_HEIGHT];

void field_init(int width, int height, int mines) {

}

void field_draw(int offset_x, int offset_y) {
    grfBeginDraw();

    grfEndDraw();
}