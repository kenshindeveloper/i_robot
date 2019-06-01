#if !defined(ITRIGGER_H)
#define ITRIGGER_H

#include "raylib.h"
#include "bullet.h"

typedef struct Trigger {
    Rectangle rectangle;
    Color color;

    Image image;
    Texture2D texture;
    
    int maxBullet;
    Bullet* bullets;

}Trigger;

Trigger NewTrigger(Rectangle, Color);

void DeleteTrigger(Trigger*);

void EventTrigger(Trigger*, Vector2, bool, bool);

void DrawTrigger(Trigger*);

void Shoot(Trigger*, bool);

#endif //ITRIGGER_H