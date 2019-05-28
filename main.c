#include <stdio.h>
#include "raylib.h"
#include "header/config.h"
#include "header/global.h"
#include "header/player.h"
#include "header/map.h"
#include "header/grid.h"

Config config;
Global global;

int main(int argc, char* argv[]) {
    config = NewConfig();
    global = NewGlobal();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.screenWidth, config.screenHeight, config.title);
    SetTargetFPS(config.fps);
    SetExitKey(KEY_F8);
    
    Player player = NewPlayer((Vector2) {500.0f, 800.0f});
    global.camera.target = player.position;
    Map map = NewMap("resources/maps/map_0.csv", "resources/sprites/tiles.png", (Vector2) {64, 20}, (Vector2) {3, 5});

    while(!WindowShouldClose()) {
        EventGlobal(&global);
        EventPlayer(&player, &map);
        ClearBackground(global.background);
        BeginDrawing();
            BeginMode2D(global.camera);
                DrawPlayer(&player);
                DrawMap(&map);
                DrawGlobal(&global);
            EndMode2D();
        EndDrawing();
    }
    DeletePlayer(&player);
    DeleteMap(&map);
    CloseWindow();

    return 0;
}

