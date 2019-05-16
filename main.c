#include <stdio.h>
#include "raylib.h"
#include "header/config.h"
#include "header/player.h"
#include "header/map.h"

Config config;

int main(int argc, char* argv[]) {
    config = NewConfig();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.screenWidth, config.screenHeight, config.title);
    SetTargetFPS(config.fps);
    SetExitKey(KEY_F8);
    
    Player player = NewPlayer((Vector2) {0.0f, 0.0f});
    Map map = NewMap("resources/maps/map_0.csv", (Vector2) {32, 16});
    printf("value: %d\n", ReadFileMap(&map));

    while(!WindowShouldClose()) {
        EventPlayer(&player);

        ClearBackground(BLACK);
        BeginDrawing();
            DrawPlayer(&player);
        EndDrawing();
    }
    DeletePlayer(&player);
    DeleteMap(&map);
    CloseWindow();

    return 0;
}
