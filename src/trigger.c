#include <stdio.h>
#include <stdlib.h>
#include "../header/trigger.h"
#include "../header/global.h"

extern Global global;

Trigger NewTrigger(Rectangle rectangle, Color color) {
    Trigger trigger = {0};
    trigger.rectangle = rectangle;
    trigger.color = color;

    trigger.image = LoadImage("resources/sprites/smoke.png");
    ImageResizeNN(&trigger.image, trigger.image.width/2, trigger.image.height/2);
    trigger.texture = LoadTextureFromImage(trigger.image);
    
    trigger.maxBullet = 5;
    trigger.bullets = (Bullet*) malloc(sizeof(Bullet)*trigger.maxBullet);

    for (int i=0; i < trigger.maxBullet; i++) 
        trigger.bullets[i] = NewBullet((Vector2) {trigger.texture.width, trigger.texture.height});

    return trigger;
}

void DeleteTrigger(Trigger* trigger) {
    UnloadImage(trigger->image);

    if (trigger->bullets != NULL) {
        free(trigger->bullets);
        trigger->bullets = NULL; 
    } 
}

void EventTrigger(Trigger* trigger, Vector2 position, bool isLeft, bool isJumping) {
    trigger->rectangle.x =  (isLeft)?(position.x + 48):(position.x + 128);
    trigger->rectangle.y = (isJumping)?(position.y + 92):(position.y + 98);

    if (IsKeyPressed(KEY_SPACE))
        Shoot(trigger, isLeft);

    for (int i=0; i < trigger->maxBullet; i++) {
        if (trigger->bullets[i].active)
            EventBullet(&trigger->bullets[i]);
    }
}

void DrawTrigger(Trigger* trigger) {
    if (global.isViewShape)
        DrawRectangleRec(trigger->rectangle, trigger->color);

    for (int i=0; i < trigger->maxBullet; i++)  {
        if (trigger->bullets[i].active) {
            DrawBullet(&trigger->bullets[i], &trigger->texture);
        }
    }
}

void Shoot(Trigger* trigger, bool isLeft) {
    for (int i=0; i < trigger->maxBullet; i++) {
        if (!trigger->bullets[i].active) {
            ActivateBullet(&trigger->bullets[i], (Vector2){trigger->rectangle.x, trigger->rectangle.y}, isLeft);
            i = trigger->maxBullet;
        }
    }
}