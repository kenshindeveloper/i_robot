#if !defined(IPLAYER_H)
#define IPLAYER_H

#include "raylib.h"
#include "animator.h"
#include "shape.h"

typedef struct Player {
    Vector2 position;
    Animator animator;
    bool isLeft;
    Shape shape;

    float velocity;

}Player;

Player NewPlayer(Vector2);

void DeletePlayer(Player*);

void EventPlayer(Player*);

void DrawPlayer(Player*);

#endif //IPLAYER_H