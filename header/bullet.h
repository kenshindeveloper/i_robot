/**
 * @file bullet.h
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para la estructura bullet.
 * @version 0.1
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */
#if !defined(IBULLET_H)
#define IBULLET_H

#include "raylib.h"
#include "shape.h"
#include "explotion.h"

typedef struct Bullet {
    Vector2 position;
    float velocity;
    bool isLeft;
    bool active;
    bool stop;
    Shape shape;
    Explotion explotion;

}Bullet;

Bullet NewBullet(Vector2 size);

void EventBullet(Bullet *bullet);

void DrawBullet(Bullet *bullet, Texture2D *texture);

void ActivateBullet(Bullet *bullet, Vector2 position, bool isLeft);

void DeactivateBullet(Bullet *bullet);

void DeleteBullet(Bullet *bullet);

#endif //IBULLET_H