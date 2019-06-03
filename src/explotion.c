/**
 * @file explotion.c
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para generacion de explosiones.
 * @version 0.1
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "../header/explotion.h"


/**
 * @brief Funcion <i>static</i> creada solo para ser invocada en el fichero
 * explotion.c.
 * 
 * Se encarga de la inicializacion, es llamada dentro de la funcion
 * <b>NewExplotion</b> 
 * @see NewExplotion
 * @param explotion Puntero a una extrutura tipo Explotion.
 * @return Nada.
 */
static void _InitExplotion(Explotion *explotion) {
    explotion->contParticles = 0;
    for (int i=0; i < explotion->numParticles; i++) {
        explotion->particles[i].position = (Vector2) {0.0f, 0.0f};
        explotion->particles[i].color = (Color) {43, 43, 38, 255};
        explotion->particles[i].alpha = 1.0f;
        explotion->particles[i].size = (float) GetRandomValue(1, 3) / 20.0f;
        explotion->particles[i].rotation = 0.0f;
        explotion->particles[i].angle = (float) GetRandomValue(90, 270);
        explotion->particles[i].active = false;
    }
}

static bool _IsAllActive(Explotion *explotion) {

    for (int i=0; i < explotion->numParticles; i++) {
        if (!explotion->particles[i].active)
            return false;
    }

    return true;
}

Explotion NewExplotion(int numParticles) {
    Explotion explotion = {0};
    explotion.particles = (Particle*) malloc(sizeof(Particle) * numParticles);
    explotion.numParticles = numParticles;
    explotion.texture = LoadTexture("resources/sprites/smoke.png");
    explotion.contParticles = 0;
    _InitExplotion(&explotion);
    
    return explotion;
}

bool EventExplotion(Explotion *explotion, Vector2 position, bool isLeft) {
    if (explotion->contParticles < explotion->numParticles) {
        for (int i=0; i < explotion->numParticles; i++) {
            if (!explotion->particles[i].active) {
                explotion->particles[i].position = position;
                explotion->particles[i].alpha = 1.0f;
                explotion->particles[i].rotation = 0.0f;
                explotion->particles[i].active = true;
                explotion->contParticles++;
                i = explotion->numParticles;
            }
        }
    }

    for (int i=0; i < explotion->numParticles; i++) {
        if (explotion->particles[i].active) {
            explotion->particles[i].position.x += cos(DEG2RAD * explotion->particles[i].angle) * 5 * ((isLeft)?(-1):(1));
            explotion->particles[i].position.y += sin(DEG2RAD * explotion->particles[i].angle) * 5 * ((isLeft)?(-1):(1));
            explotion->particles[i].alpha -= 0.04f;
            if (explotion->particles[i].alpha <= 0.0f)
                explotion->particles[i].active = false;
        }
    }

    if (explotion->contParticles >= explotion->numParticles && !_IsAllActive(explotion)) {
        _InitExplotion(explotion);
        return true;
    }

    return false;
}

void DrawExplotion(Explotion *explotion) {
    for (int i=0; i < explotion->numParticles; i++) {
        if (explotion->particles[i].active) {
            DrawTexturePro(
                explotion->texture,
                (Rectangle) {0.0f, 0.0f, explotion->texture.width, explotion->texture.height},
                (Rectangle) {
                    explotion->particles[i].position.x, 
                    explotion->particles[i].position.y,
                    explotion->texture.width*explotion->particles[i].size,
                    explotion->texture.height*explotion->particles[i].size
                },
                (Vector2) {
                    explotion->texture.width*explotion->particles[i].size/2,
                    explotion->texture.height*explotion->particles[i].size/2
                },
                explotion->particles[i].rotation,
                Fade(explotion->particles[i].color, explotion->particles[i].alpha)
            );
        }
    }
}

void DeleteExplotion(Explotion *explotion) {
    if (explotion->particles != NULL) {
        free(explotion->particles);
        explotion->particles = NULL;
    }
    UnloadTexture(explotion->texture);
}