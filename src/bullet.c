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
    bullet.velocity = 15.0f;
    bullet.shape = NewShape(bullet.position, size, RAYWHITE);
    return bullet;
}

void EventBullet(Bullet* bullet) {
    bullet->position.x += bullet->velocity * ((bullet->isLeft)?(-1):(1));
    SetPositionShape(&bullet->shape, bullet->position);
}

void DrawBullet(Bullet* bullet, Texture2D* texture) {
    if (bullet->active) {
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

    if (CheckCollisions(collisions, &playerRect)) {
        printf("bullet desactivado...\n");
        DeactivateBullet(bullet);
    }

}

void ActivateBullet(Bullet* bullet, Vector2 position, bool isLeft) {
   bullet->active = true;
   bullet->position = position;
   bullet->isLeft = isLeft;
}

void DeactivateBullet(Bullet* bullet) {
    bullet->active = false;
    bullet->position = (Vector2) {0.0f, 0.0f};
}
