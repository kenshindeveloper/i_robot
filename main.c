#include "raylib.h"
#include "header/config.h"
#include "header/player.h"


Config config;

int main(int argc, char* argv[]) {
    config = NewConfig();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config.screenWidth, config.screenHeight, config.title);
    SetTargetFPS(config.fps);
    SetExitKey(KEY_F8);
    
    Player player = NewPlayer((Vector2) {0.0f, 0.0f});

    while(!WindowShouldClose()) {
        EventPlayer(&player);

        ClearBackground(BLACK);
        BeginDrawing();
            DrawPlayer(&player);
        EndDrawing();
    }
    DeletePlayer(&player);
    CloseWindow();
    return 0;
}