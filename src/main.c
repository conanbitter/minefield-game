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
#define STATE_LOOSE (1)

int current_difficulty = 1;
int state = STATE_NORMAL;
int selected_x = 0;
int selected_y = 0;

void new_game(int difficulty) {
    switch (difficulty) {
    case 1:
        fieldInit(9, 9, 10);
        break;
    case 2:
        fieldInit(16, 16, 40);
        break;
    case 3:
        fieldInit(30, 16, 40);
        break;
    }
    fieldPopulate(10, 0);
    grfBeginDraw();
    grfClear();
    grfMoveTo(FIELD_OFFSET_X - 1, FIELD_OFFSET_Y - 1);
    grfLineTo(field_width * FIELD_CELL_SIZE + FIELD_OFFSET_X, FIELD_OFFSET_Y - 1);
    grfLineTo(field_width * FIELD_CELL_SIZE + FIELD_OFFSET_X, field_height * FIELD_CELL_SIZE + FIELD_OFFSET_Y);
    grfLineTo(FIELD_OFFSET_X - 1, field_height * FIELD_CELL_SIZE + FIELD_OFFSET_Y);
    grfLineTo(FIELD_OFFSET_X - 1, FIELD_OFFSET_Y - 1);
    for (int i = 0;i < field_size;i++) {
        fieldDrawCellInd(i);
    }
    grfEndDraw();
    state = STATE_NORMAL;
}


void OnLoad() {
    atlas_init();
    new_game(1);
}

void OnMouseDown(int button, int x, int y) {
    if (state == STATE_NORMAL) {
        int cell_index = fieldCellByScreenXY(x, y);
        if (cell_index >= 0) {
            switch (button)
            {
            case GRF_BUTTON_LEFT:
                if (fieldIsClosed(cell_index)) {
                    //grfBeginDraw();
                    //atlas_draw(FIELD_OFFSET_X + fx * FIELD_CELL_SIZE, FIELD_OFFSET_Y + fy * FIELD_CELL_SIZE, &CELL_CLOSED_DOWN);
                    //grfEndDraw();
                    //field_open(fx, fy);
                }
                break;
            case GRF_BUTTON_RIGHT:
                fieldMark(cell_index);

            default:
                break;
            }
        }
    }
}

void OnMouseUp(int button, int x, int y) {
    int fx, fy;
    if (state == STATE_NORMAL) {
        int cell_index = fieldCellByScreenXY(x, y);
        if (cell_index >= 0) {
            switch (button)
            {
            case GRF_BUTTON_LEFT:
                if (fieldIsClosed(cell_index)) {
                    //grfBeginDraw();
                    //atlas_draw(FIELD_OFFSET_X + fx * FIELD_CELL_SIZE, FIELD_OFFSET_Y + fy * FIELD_CELL_SIZE, &CELL_CLOSED_DOWN);
                    //grfEndDraw();
                    int res = fieldOpen(cell_index);
                    if (res == RESULT_LOOSE) {
                        state = STATE_LOOSE;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
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
