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
#define STATE_GAME_OVER (1)
#define STATE_BEFORE_OPEN (2)

int current_difficulty = 1;
int state = STATE_NORMAL;
int selected = -1;
bool hovering = false;
int other_mouse_button = 0;

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
                if (cellIsClosed(cell_index)) {
                    grfBeginDraw();
                    fieldDrawCellCustomInd(cell_index, &CELL_CLOSED_DOWN);
                    grfEndDraw();
                    selected = cell_index;
                    hovering = true;
                    state = STATE_BEFORE_OPEN;
                } else if (cellIsOpen(cell_index)) {
                    // DISCOVER
                }
                break;
            case GRF_BUTTON_RIGHT:
                if (cellIsOpen(cell_index)) {
                    // DISCOVER
                } else {
                    fieldMark(cell_index);
                }
            default:
                break;
            }
        }
    }
}

void OnMouseMove(int x, int y) {
    switch (state)
    {
    case STATE_BEFORE_OPEN:
        int cell_index = fieldCellByScreenXY(x, y);
        if (cell_index != selected && hovering) {
            grfBeginDraw();
            fieldDrawCellInd(selected);
            grfEndDraw();
            hovering = false;
        }
        if (cell_index == selected && !hovering) {
            grfBeginDraw();
            fieldDrawCellCustomInd(cell_index, &CELL_CLOSED_DOWN);
            grfEndDraw();
            hovering = true;
        }
        break;

    default:
        break;
    }
}

void OnMouseUp(int button, int x, int y) {
    switch (state)
    {
    case STATE_BEFORE_OPEN:
        if (button == GRF_BUTTON_LEFT) {
            state = STATE_NORMAL;
            int cell_index = fieldCellByScreenXY(x, y);
            if (cell_index == selected) {
                int res = fieldOpen(cell_index);
                if (res == RESULT_LOOSE) {
                    state = STATE_GAME_OVER;
                }
            }
        }
        break;

    default:
        break;
    }
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
