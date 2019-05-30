#if !defined(IPLAYER_H)
#define IPLAYER_H

#include "raylib.h"
#include "animator.h"
#include "shape.h"
#include "map.h"
#include "trigger.h"
#include "smoke.h"

typedef struct Player {
    Vector2 position;
    Animator animator;

    bool isLeft;
    bool isGround;
    bool isJumping;
    bool isDown;
    bool isUp;

    float velocity;
    float contAnimaClose;

    Shape shape;
    Shape ground;
    Shape head;

    Trigger trigger;

    Smoke smoke;
}Player;

bool CheckCollision(Shape*, Map*);

Player NewPlayer(Vector2);

void DeletePlayer(Player*);

void EventPlayer(Player*, Map*);

void DrawPlayer(Player*);

bool IsGround(Player*, Map*);

#endif //IPLAYER_H