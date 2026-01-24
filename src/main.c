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


void OnLoad() {
    atlas_init();
    field_init(9, 9, 10);
    field_draw(BORDER, BORDER);
    grfBeginDraw();
    for (int y = 0;y < 9;y++) {
        for (int x = 0;x < 9;x++) {
            int c = rand() % 15;
            if (c == 9) {
                atlas_draw(x * FIELD_CELL_SIZE + 20, y * FIELD_CELL_SIZE + 20, &CELL_MINE);
            } else if (c >= 10) {
                atlas_draw(x * FIELD_CELL_SIZE + 20, y * FIELD_CELL_SIZE + 20, &CELL_CLOSED);
            } else {
                atlas_draw(x * FIELD_CELL_SIZE + 20, y * FIELD_CELL_SIZE + 20, &CELL_DIGITS[c]);
            }
        }
    }
    grfEndDraw();
}

void OnMouseDown(int button, int x, int y) {
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

    grfStart(app_instance,
        L"Minefield",
        500,
        500);
    return 0;
}
