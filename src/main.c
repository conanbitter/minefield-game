#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "grf.h"
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "field.h"
#include "atlas.h"

#define BORDER (3)

HINSTANCE app_instance;

#define STATE_NORMAL (0)

int current_difficulty = 1;
int state = STATE_NORMAL;
int selected_x = 0;
int selected_y = 0;

void new_game(int difficulty) {
    switch (difficulty) {
    case 1:
        field_init(9, 9, 10);
        break;
    case 2:
        field_init(16, 16, 40);
        break;
    case 3:
        field_init(16, 16, 40);
        break;
    }
    field_populate(10, 4, 4);
    grfBeginDraw();
    grfClear();
    grfMoveTo(FIELD_OFFSET_X - 1, FIELD_OFFSET_Y - 1);
    grfLineTo(field_width * FIELD_CELL_SIZE + FIELD_OFFSET_X, FIELD_OFFSET_Y - 1);
    grfLineTo(field_width * FIELD_CELL_SIZE + FIELD_OFFSET_X, field_height * FIELD_CELL_SIZE + FIELD_OFFSET_Y);
    grfLineTo(FIELD_OFFSET_X - 1, field_height * FIELD_CELL_SIZE + FIELD_OFFSET_Y);
    grfLineTo(FIELD_OFFSET_X - 1, FIELD_OFFSET_Y - 1);
    for (int y = 0;y < field_height;y++) {
        for (int x = 0;x < field_width;x++) {
            //atlas_draw(x * FIELD_CELL_SIZE + FIELD_OFFSET_X, y * FIELD_CELL_SIZE + FIELD_OFFSET_Y, &CELL_CLOSED);
            field_draw_cell(x, y);
        }
    }
    grfEndDraw();
    state = STATE_NORMAL;
}


void OnLoad() {
    atlas_init();
    new_game(1);
}

void OnMouseDown(int button, int x, int y) {
    int fx, fy;
    switch (button)
    {
    case GRF_BUTTON_LEFT:
        if (field_coord(x, y, &fx, &fy) && field_is_closed(fx, fy)) {
            //grfBeginDraw();
            //atlas_draw(FIELD_OFFSET_X + fx * FIELD_CELL_SIZE, FIELD_OFFSET_Y + fy * FIELD_CELL_SIZE, &CELL_CLOSED_DOWN);
            //grfEndDraw();
            field_open(fx, fy);
        }
        break;
    case GRF_BUTTON_RIGHT:
        if (field_coord(x, y, &fx, &fy)) {
            field_mark(fx, fy);
        }

    default:
        break;
    }
}

void OnMouseUp(int button, int x, int y) {
}

void OnMouseMove(int x, int y) {
}

void OnKeyDown(int key) {
}

void OnKeyUp(int key) {
}

void OnFinish() {
    atlas_free();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    app_instance = hInstance;

    grfSetOnMouseDown(&OnMouseDown);
    grfSetOnMouseUp(&OnMouseUp);
    grfSetOnMouseMove(&OnMouseMove);
    grfSetOnKeyDown(&OnKeyDown);
    grfSetOnKeyUp(&OnKeyUp);
    grfSetOnLoad(&OnLoad);
    grfSetOnExit(&OnFinish);

    grfSetFillColor(199, 207, 211);
    grfSetLineColor(36, 70, 93);

    grfStart(app_instance,
        L"Minefield",
        500,
        600);
    return 0;
}
