#if !defined(IBULLET_H)
#define IBULLET_H

#include "raylib.h"
#include "shape.h"

typedef struct Bullet {
    Vector2 position;
    float velocity;
    bool isLeft;
    bool active;
    Shape shape;

}Bullet;

Bullet NewBullet(Vector2);

void EventBullet(Bullet*);

void DrawBullet(Bullet*, Texture2D*);

void ActivateBullet(Bullet*, Vector2, bool);

void DeactivateBullet(Bullet*);

#endif //IBULLET_H