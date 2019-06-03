/**
 * @file smoke.h
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para generacion de particulas en el jetpack.
 * @version 1.0
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */

#if !defined(ISMOKE_H)
#define ISMOKE_H

#include "particle.h"

typedef struct Smoke {
    Texture2D texture;
    Particle *particles;
    int num;

}Smoke;

Smoke NewSmoke(const char* path, int num);

void EventSmoke(Smoke *smoke, Vector2 position, bool isLeft, bool isUp);

void DrawSmoke(Smoke *smoke);

void DeleteSmoke(Smoke *smoke);

#endif //ISMOKE_H