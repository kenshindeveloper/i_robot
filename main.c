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
    
    Player player = NewPlayer((Vector2) {100.0f, 100.0f});
    global.camera.target = player.position;

    Map map = NewMap("resources/maps/map_0.csv", "resources/sprites/tiles.png", (Vector2) {32, 16}, (Vector2) {3, 5});
    
    Grid grid = NewGrid((Vector2) {20, 20});

    while(!WindowShouldClose()) {
        EventPlayer(&player, &map);

        ClearBackground(BLACK);
        BeginDrawing();
            BeginMode2D(global.camera);
                DrawIGrid(&grid);
                DrawMap(&map);
                DrawPlayer(&player);
            EndMode2D();
        EndDrawing();
    }
    DeletePlayer(&player);
    DeleteMap(&map);
    CloseWindow();

    return 0;
}

