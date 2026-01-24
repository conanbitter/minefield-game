#include "atlas.h"
#include "grf.h"

static GRFImage atlas;

void atlas_init() {
    atlas = grfLoadImageFromRes(L"bmAtlas");
}

void atlas_draw(int x, int y, const GRFRect* rect) {
    grfDrawImage(atlas, x, y, rect);
}

void atlas_free() {
    grfFreeImage(atlas);
}