#include <stdio.h>
#include "../header/global.h"

Global NewGlobal() {
    Global global;
    global.camera.offset = (Vector2) {-840, -1670};
    global.camera.rotation = 0.0f;
    global.camera.zoom = 1.0f;

    global.valueMinTile = -100;
    global.power = 100;
    global.contPower = 0.0f;

    global.groundColor = (Color) {255.0f, 0.0f, 0.0f, 155.0f};
    global.background = (Color) {224.0f, 219.0f, 205.0f, 255.0f};

    global.isViewGrid = false;
    global.isViewShape = false;
    global.isViewCursor = false;

    global.grid = NewGrid((Vector2){600, 600});

    return global;
}

void EventGlobal(Global* global) {
    if (IsKeyPressed(KEY_F1)) 
        global->isViewGrid = !global->isViewGrid;
    
    if (IsKeyPressed(KEY_F2))
        global->isViewShape = !global->isViewShape;

    if (IsCursorHidden() && global->isViewCursor)
        ShowCursor();
    else if (!IsCursorHidden() && !global->isViewCursor)
        HideCursor();
}

void DrawGlobal(Global* global) {
    if (global->isViewGrid)
        DrawIGrid(&global->grid);
}   