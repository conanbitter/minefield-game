#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include "grf.h"
#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "field.h"
#include "atlas.h"
#include "ui.h"

#define BORDER (3)

HINSTANCE app_instance;

#define STATE_NORMAL (0)
#define STATE_GAME_OVER (1)
#define STATE_BEFORE_OPEN (2)
#define STATE_MAYBE_DISCOVER (3)
#define STATE_BEFORE_DISCOVER (4)
#define STATE_BUTTON_PRESSED (5)

int current_difficulty = 1;
int state = STATE_NORMAL;
int selected = -1;
int candidates[8];
bool hovering = false;
int other_mouse_button = 0;
Button* selected_button;

Button buttons[4];

#define BTN_SMILE (0)
#define BTN_EASY (1)
#define BTN_MEDIUM (2)
#define BTN_HARD (3)

void newGame(int difficulty) {
    grfBeginDraw();
    grfClear();
    switch (difficulty) {
    case 1:
        fieldInit(9, 9, 10);
        buttons[BTN_SMILE].x = 190;
        buttons[BTN_SMILE].y = 2;
        buttons[BTN_SMILE].face = SMILE_NORMAL;
        buttons[BTN_EASY].x = 42;
        buttons[BTN_EASY].y = 530;
        buttons[BTN_EASY].face = DIFFICULTY_EASY_ACTIVE;
        buttons[BTN_MEDIUM].x = 173;
        buttons[BTN_MEDIUM].y = 530;
        buttons[BTN_MEDIUM].face = DIFFICULTY_MEDIUM;
        buttons[BTN_HARD].x = 303;
        buttons[BTN_HARD].y = 530;
        buttons[BTN_HARD].face = DIFFICULTY_HARD;
        for (int i = 0;i < 4;i++) {
            btnDraw(&buttons[i]);
        }
        break;
    case 2:
        fieldInit(16, 16, 40);
        break;
    case 3:
        fieldInit(30, 16, 40);
        break;
    }
    current_difficulty = difficulty;
    fieldPopulate(10, 0);
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

void onButtonPress(int id) {
    switch (id)
    {
    case BTN_SMILE:
        newGame(current_difficulty);
        break;
    case BTN_EASY:
        selected = -1;
        break;
    case BTN_MEDIUM:
        selected = -1;
        break;
    case BTN_HARD:
        selected = -1;
        break;

    default:
        break;
    }
}

void OnLoad() {
    buttons[BTN_SMILE].id = BTN_SMILE;
    buttons[BTN_SMILE].width = SMILE_NORMAL.normal->w;
    buttons[BTN_SMILE].height = SMILE_NORMAL.normal->h;
    buttons[BTN_EASY].id = BTN_EASY;
    buttons[BTN_EASY].width = DIFFICULTY_EASY.normal->w;
    buttons[BTN_EASY].height = DIFFICULTY_EASY.normal->h;
    buttons[BTN_MEDIUM].id = BTN_MEDIUM;
    buttons[BTN_MEDIUM].width = DIFFICULTY_MEDIUM.normal->w;
    buttons[BTN_MEDIUM].height = DIFFICULTY_MEDIUM.normal->h;
    buttons[BTN_HARD].id = BTN_HARD;
    buttons[BTN_HARD].width = DIFFICULTY_HARD.normal->w;
    buttons[BTN_HARD].height = DIFFICULTY_HARD.normal->h;
    atlas_init();
    newGame(1);
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
                    fieldDrawCellPressedInd(cell_index);
                    btnDrawCustom(&buttons[BTN_SMILE], &SMILE_OPEN);
                    grfEndDraw();
                    selected = cell_index;
                    hovering = true;
                    state = STATE_BEFORE_OPEN;
                } else if (cellIsOpen(cell_index)) {
                    fieldTryDiscover(cell_index, &candidates);
                    if (candidates[0] > 0) {
                        state = STATE_MAYBE_DISCOVER;
                        other_mouse_button = button;
                        selected = cell_index;
                        hovering = true;
                    }
                }
                break;
            case GRF_BUTTON_RIGHT:
                if (cellIsOpen(cell_index)) {
                    fieldTryDiscover(cell_index, &candidates);
                    if (candidates[0] > 0) {
                        state = STATE_MAYBE_DISCOVER;
                        other_mouse_button = button;
                        selected = cell_index;
                        hovering = true;
                    }
                } else {
                    fieldMark(cell_index);
                }
            default:
                break;
            }
        } else {
            for (int i = 0;i < 4;i++) {
                if (btnIsInside(&buttons[i], x, y)) {
                    selected_button = &buttons[i];
                    hovering = true;
                    state = STATE_BUTTON_PRESSED;
                    grfBeginDraw();
                    btnDrawPressed(selected_button);
                    grfEndDraw();
                    break;
                }
            }
        }
    } else if (state == STATE_MAYBE_DISCOVER && (button == GRF_BUTTON_LEFT || button == GRF_BUTTON_RIGHT)) {
        int cell_index = fieldCellByScreenXY(x, y);
        if (other_mouse_button != button && cell_index == selected) {
            state = STATE_BEFORE_DISCOVER;
            grfBeginDraw();
            for (int i = 0;i < 8;i++) {
                if (candidates[i] < 0) break;
                fieldDrawCellPressedInd(candidates[i]);
            }
            grfEndDraw();
        } else {
            state = STATE_NORMAL;
        }
    } else if (state == STATE_GAME_OVER) {
        for (int i = 0;i < 4;i++) {
            if (btnIsInside(&buttons[i], x, y)) {
                selected_button = &buttons[i];
                hovering = true;
                state = STATE_BUTTON_PRESSED;
                grfBeginDraw();
                btnDrawPressed(selected_button);
                grfEndDraw();
                break;
            }
        }
    }
}

void OnMouseMove(int x, int y) {
    int cell_index;
    switch (state)
    {
    case STATE_BEFORE_OPEN:
        cell_index = fieldCellByScreenXY(x, y);
        if (cell_index != selected && hovering) {
            grfBeginDraw();
            fieldDrawCellInd(selected);
            grfEndDraw();
            hovering = false;
        }
        if (cell_index == selected && !hovering) {
            grfBeginDraw();
            fieldDrawCellPressedInd(cell_index);
            grfEndDraw();
            hovering = true;
        }
        break;
    case STATE_BEFORE_DISCOVER:
        cell_index = fieldCellByScreenXY(x, y);
        if (cell_index != selected && hovering) {
            grfBeginDraw();
            for (int i = 0;i < 8;i++) {
                if (candidates[i] < 0) break;
                fieldDrawCellInd(candidates[i]);
            }
            grfEndDraw();
            hovering = false;
        }
        if (cell_index == selected && !hovering) {
            grfBeginDraw();
            for (int i = 0;i < 8;i++) {
                if (candidates[i] < 0) break;
                fieldDrawCellPressedInd(candidates[i]);
            }
            grfEndDraw();
            hovering = true;
        }
        break;
    case STATE_BUTTON_PRESSED:
        if (btnIsInside(selected_button, x, y)) {
            if (!hovering) {
                grfBeginDraw();
                btnDrawPressed(selected_button);
                grfEndDraw();
                hovering = true;
            }
        } else {
            if (hovering) {
                grfBeginDraw();
                btnDraw(selected_button);
                grfEndDraw();
                hovering = false;
            }
        }
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
            grfBeginDraw();
            btnDraw(&buttons[BTN_SMILE]);
            grfEndDraw();
            if (cell_index == selected) {
                int res = fieldOpen(cell_index);
                if (res == RESULT_LOOSE) {
                    state = STATE_GAME_OVER;
                }
            }
        }
        break;
    case STATE_BEFORE_DISCOVER:
        if (button == GRF_BUTTON_LEFT || button == GRF_BUTTON_RIGHT) {
            state = STATE_NORMAL;
            int cell_index = fieldCellByScreenXY(x, y);
            if (cell_index == selected) {
                int res = fieldDiscover(cell_index);
                if (res == RESULT_LOOSE) {
                    state = STATE_GAME_OVER;
                } else if (res == RESULT_ABORT) {
                    grfBeginDraw();
                    for (int i = 0;i < 8;i++) {
                        if (candidates[i] < 0) break;
                        fieldDrawCellInd(candidates[i]);
                    }
                    grfEndDraw();
                }
            }
        }
        break;
    case STATE_BUTTON_PRESSED:
        if (hovering) {
            grfBeginDraw();
            btnDraw(selected_button);
            grfEndDraw();
        }
        state = STATE_NORMAL;
        if (btnIsInside(selected_button, x, y)) {
            onButtonPress(selected_button->id);
        }
    default:
        break;
    }
}

void OnLostFocus() {
    if (state == STATE_BEFORE_OPEN) {
        grfBeginDraw();
        fieldDrawCellInd(selected);
        grfEndDraw();
    }
    if (state == STATE_BEFORE_DISCOVER) {
        grfBeginDraw();
        for (int i = 0;i < 8;i++) {
            if (candidates[i] < 0) break;
            fieldDrawCellInd(candidates[i]);
        }
        grfEndDraw();
    }
    state = STATE_NORMAL;
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
    grfSetOnLostFocus(&OnLostFocus);

    grfSetFillColor(199, 207, 211);
    grfSetLineColor(36, 70, 93);

    grfStart(app_instance,
        L"Minefield",
        500,
        600);
    return 0;
}
