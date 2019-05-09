#if !defined(IANIMATOR_H)
#define IANIMATOR_H


#include "raylib.h"
#include "animation.h"

typedef struct Animator {
    const char* path;
    Image image;
    Texture2D texture;
    Animation* animations;
    int index;
    int numAnimations;
    int currentIndex;
    float scale;
    Vector2 dimension;
}Animator;

Animator NewAnimator(const char*, int, float, Vector2);

bool PushAnimationAnimator(Animator*, Animation);

bool DeleteAnimator(Animator*);

Vector2 ImageQuadAnimator(Animator*);

void SetAnimation(Animator*, const char*);

void DrawAnimator(Animator*, Vector2);

#endif //IANIMATOR_H