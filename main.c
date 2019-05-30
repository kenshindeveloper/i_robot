#include <stdio.h>
#include "raylib.h"
#include "header/config.h"
#include "header/global.h"
#include "header/player.h"
#include "header/map.h"
#include "header/grid.h"
#include "header/gui.h"

Config config;
Global global;

int main(int argc, char* argv[]) {
    config = NewConfig();
    global = NewGlobal();
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(config.screenWidth, config.screenHeight, config.title);
    SetTargetFPS(config.fps);
    SetExitKey(KEY_F8);
    Player player = NewPlayer((Vector2) {1090.0f, 1870.0f});
    global.camera.target = player.position;
    Map map = NewMap("resources/maps/map_0.csv", "resources/sprites/tiles.png", (Vector2) {64, 20}, (Vector2) {3, 5});

    Gui gui = NewGui((Rectangle) {0, 0, config.screenWidth, 60.0f}, (Color) {43.0f, 43.0f, 38.0f, 255.0f});

    while(!WindowShouldClose()) {
        EventGlobal(&global);
        EventPlayer(&player, &map);
        EventGui(&gui);
        ClearBackground(global.background);
        BeginDrawing();
            BeginMode2D(global.camera);
                DrawPlayer(&player);
                DrawMap(&map);
                DrawGlobal(&global);
            EndMode2D();
            DrawGui(&gui);
        EndDrawing();
    }
    DeletePlayer(&player);
    DeleteMap(&map);
    DeleteGui(&gui);
    CloseWindow();

    return 0;
}
