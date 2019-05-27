#include "../header/global.h"

Global NewGlobal() {
    Global global;
    global.camera.offset = (Vector2) {0, 0};
    global.camera.rotation = 0.0f;
    global.camera.zoom = 1.0f;

    global.valueMinTile = -100;
    global.groundColor = (Color) {255.0f, 0.0f, 0.0f, 155.0f};

    return global;
}