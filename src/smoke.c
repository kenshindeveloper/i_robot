/**
 * @file smoke.c
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para generacion de particulas en el jetpack.
 * @version 1.0
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../header/smoke.h"

Smoke NewSmoke(const char* path, int num) {
    Smoke smoke = {0};
    smoke.num = num;
    smoke.texture = LoadTexture(path);
    smoke.particles = (Particle*) malloc(sizeof(Particle)*num);

    for (int i=0; i < num; i++) {
        smoke.particles[i].position = (Vector2) {0.0f, 0.0f};
        smoke.particles[i].color = (Color) {43, 43, 38, 255},
        smoke.particles[i].alpha = 1.0f;
        smoke.particles[i].size = (float) GetRandomValue(1, 3) /20.0f; 
        smoke.particles[i].rotation = 1.0f;
        smoke.particles[i].angle = 0.0f;
        smoke.particles[i].active = false;
    }

    return smoke;
}

void EventSmoke(Smoke *smoke, Vector2 position, bool isLeft, bool isUp) {
    if (isUp) {
        for (int i=0; i < smoke->num; i++) {
            if (!smoke->particles[i].active) {
                if (!isLeft)
                    smoke->particles[i].position = (Vector2) {position.x+80, position.y+120};
                else
                    smoke->particles[i].position = (Vector2) {position.x+110, position.y+120};

                smoke->particles[i].alpha = 1.0f;
                smoke->particles[i].active = true;
                i = smoke->num;
            }
        }
    }

    for (int i=0; i < smoke->num; i++) {
        if (smoke->particles[i].active) {
            smoke->particles[i].position.y += 3.0f;
            smoke->particles[i].rotation += 5.0f;
            smoke->particles[i].alpha -= 0.01f;

            if (smoke->particles[i].alpha <= 0.0f)
                smoke->particles[i].active = false;
        }
    }
}

void DrawSmoke(Smoke* smoke) {
    for (int i=0; i < smoke->num; i++) {
        if (smoke->particles[i].active) {
            DrawTexturePro(
                smoke->texture,
                (Rectangle) {0.0f, 0.0f, smoke->texture.width, smoke->texture.height},
                (Rectangle) {smoke->particles[i].position.x, smoke->particles[i].position.y, smoke->texture.width*smoke->particles[i].size, smoke->texture.height*smoke->particles[i].size},
                (Vector2) {smoke->texture.width*smoke->particles[i].size/2, smoke->texture.height*smoke->particles[i].size/2},
                smoke->particles[i].rotation,
                Fade(smoke->particles[i].color, smoke->particles[i].alpha)
            );
        }
    }
}

void DeleteSmoke(Smoke* smoke) {
    if (smoke->particles != NULL) {
        free(smoke->particles);
        smoke->particles = NULL;
    }
    UnloadTexture(smoke->texture);
}