/**
 * @file bullet.c
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para la estructura bullet.
 * @version 0.1
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */
#include <stdio.h>
#include "../header/bullet.h"
#include "../header/collisions.h"

extern Collisions* collisions;

/**
 * Crea una estructura tipo Bullet
 * y la retorna
**/
Bullet NewBullet(Vector2 size) {
    Bullet bullet;
    bullet.position = (Vector2) {0.0f, 0.0f};
    bullet.isLeft = false;
    bullet.active = false;
    bullet.stop = false;
    bullet.velocity = 15.0f;
    bullet.shape = NewShape(bullet.position, size, RAYWHITE);
    bullet.explotion = NewExplotion(10);

    return bullet;
}

void EventBullet(Bullet* bullet) {
    if (!bullet->stop) {
        bullet->position.x += bullet->velocity * ((bullet->isLeft)?(-1):(1));
        SetPositionShape(&bullet->shape, bullet->position);
    }
    else if (EventExplotion(&bullet->explotion, bullet->position, bullet->isLeft))
        DeactivateBullet(bullet);
}

void DrawBullet(Bullet* bullet, Texture2D* texture) {
    if (bullet->active && !bullet->stop) {
        DrawTextureRec(
            *(texture),
            (Rectangle) {0.0f, 0.0f, texture->width, texture->height},
            bullet->position,
            BLACK
        );
    }

    Rectangle playerRect = (Rectangle) {
        bullet->shape.position.x, 
        bullet->shape.position.y, 
        bullet->shape.size.x,
        bullet->shape.size.y
    };

    if (bullet->stop)
        DrawExplotion(&bullet->explotion);

    else if (CheckCollisions(collisions, &playerRect))
        bullet->stop = true;
}

void ActivateBullet(Bullet* bullet, Vector2 position, bool isLeft) {
   bullet->active = true;
   bullet->position = position;
   bullet->isLeft = isLeft;
}

void DeactivateBullet(Bullet* bullet) {
    bullet->active = false;
    bullet->stop = false;
    bullet->position = (Vector2) {0.0f, 0.0f};
}

void DeleteBullet(Bullet *bullet) {
    DeleteExplotion(&bullet->explotion);
}