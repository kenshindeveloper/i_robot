#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "header/config.h"
#include "header/global.h"
#include "header/player.h"
#include "header/map.h"
#include "header/grid.h"
#include "header/gui.h"
#include "header/collisions.h"

Config config;
Global global;
Collisions* collisions;

int main(int argc, char* argv[]) {
    config = NewConfig();
    global = NewGlobal();
    collisions = NULL;
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

// #include <stdio.h>
// #include <math.h>
// #include "raylib.h"

// #define MAX_PARTICLES 15

// typedef struct {
//     Vector2 position;
//     Color color;
//     float alpha;
//     float size;
//     float rotation;
//     float angle;
//     bool active;

// }Particle;

// const int screenWidth = 640;
// const int screenHeight = 480;

// void InitParticles(Particle *particle);

// void UpdateParticles(Particle *particle);

// void DrawParticles(Particle *particle, Texture2D *texture);

// int main(int argc, char* argv[]) {
//     InitWindow(screenWidth, screenHeight, "Particles Explotion!");

//     Particle particles[MAX_PARTICLES] = {0};
//     InitParticles(particles);

//     Texture2D texture = LoadTexture("resources/sprites/smoke.png");

//     SetTargetFPS(60);
//     while (!WindowShouldClose()) {
//         UpdateParticles(particles);

//         BeginDrawing();
//             ClearBackground(RAYWHITE);
//             DrawParticles(particles, &texture);
//         EndDrawing();
//     }
//     UnloadTexture(texture);
//     CloseWindow();

//     return 0;
// }

// void InitParticles(Particle *particle) {
//     for (int i=0; i < MAX_PARTICLES; i++) {
        
//         particle[i].position = (Vector2) {0.0f, 0.0f};
//         particle[i].color = RED;//(Color) {43, 43, 38, 255};
//         particle[i].alpha = 1.0f;
//         particle[i].size = (float) GetRandomValue(1, 8) / 20.0f;
//         particle[i].rotation = 0.0f;
//         // particle[i].angle = (float) GetRandomValue(0, 180);
//         particle[i].angle = (float) GetRandomValue(90, 270);
//         particle[i].active = false;
//     }
// }

// void UpdateParticles(Particle *particle) {
//     for (int i=0; i < MAX_PARTICLES; i++) {
//         if (!particle[i].active) {
//             particle[i].position = GetMousePosition();
//             particle[i].alpha = 1.0f;
//             particle[i].rotation = 0.0f;
//             // particle[i].angle = (float) GetRandomValue(0, 180);
//             particle[i].angle = (float) GetRandomValue(90, 270);
//             particle[i].active = true;
//             i = MAX_PARTICLES;
//         }
//     }

//     for (int i=0; i < MAX_PARTICLES; i++) {
//         if (particle[i].active) {
//             particle[i].position.x += cos(DEG2RAD * particle[i].angle) * 5;
//             particle[i].position.y += sin(DEG2RAD * particle[i].angle) * 5;
//             // particle[i].rotation += 5.0f;
//             particle[i].alpha -= 0.02f;
//             if (particle[i].alpha <= 0.0f)
//                 particle[i].active = false;
//         }
//     }
// }

// void DrawParticles(Particle *particle, Texture2D *texture) {
//     for (int i=0; i < MAX_PARTICLES; i++) {
//         if (particle[i].active) {
//             DrawTexturePro(
//                 *texture,
//                 (Rectangle) {0.0f, 0.0f, texture->width, texture->height},
//                 (Rectangle) {particle[i].position.x, particle[i].position.y, texture->width*particle[i].size, texture->height*particle[i].size},
//                 (Vector2) {texture->width/2, texture->height/2},
//                 particle[i].rotation,
//                 Fade(particle[i].color, particle[i].alpha)
//             );
//         }
//     }
// }