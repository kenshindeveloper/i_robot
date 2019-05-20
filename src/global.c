#include "../header/global.h"

Global NewGlobal() {
    Global global;
    global.camera.offset = (Vector2) {0, 0};
    global.camera.rotation = 0.0f;
    global.camera.zoom = 1.0f;
    return global;
}