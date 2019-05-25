#if !defined(IPLAYER_H)
#define IPLAYER_H

#include "raylib.h"
#include "animator.h"
#include "shape.h"
#include "map.h"

typedef struct Player {
    Vector2 position;
    Animator animator;
    bool isLeft;
    Shape shape;

    float velocity;

}Player;

bool CheckCollision(Shape*, Map*);

Player NewPlayer(Vector2);

void DeletePlayer(Player*);

void EventPlayer(Player*, Map*);

void DrawPlayer(Player*);

#endif //IPLAYER_H