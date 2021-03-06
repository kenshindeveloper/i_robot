#include <stdlib.h>
#include <string.h>
#include "../header/animator.h"

Animator NewAnimator(const char* path, int numAnimation, float scale, Vector2 dimension) {
    Animator animator;
    animator.path = path; 
    animator.image = LoadImage(path);
    animator.texture = LoadTextureFromImage(animator.image);
    animator.numAnimations = numAnimation;
    animator.index = 0;
    animator.currentIndex = 0;
    animator.animations = (Animation*) malloc(sizeof(Animation)*numAnimation);
    animator.scale = scale;
    animator.dimension = dimension;
    animator._prevIndex = -1;
    animator._isLeft = true;
    animator.nameAnimation = "";

    if (scale > 1.0f) {
        ImageResizeNN(&animator.image, animator.image.width*scale, animator.image.height*scale);
        animator.texture = LoadTextureFromImage(animator.image);
    }

    return animator;
}

bool PushAnimationAnimator(Animator* animator, Animation animation) {
    if (animator->index < animator->numAnimations) {
        animator->animations[animator->index++] = animation; // asigna la animacion y aumenta el index.

        return true;
    }
    return false;
}

bool DeleteAnimator(Animator* animator) {
    UnloadImage(animator->image);
    if (animator->animations != NULL) {
        for (int i = 0; i < animator->numAnimations; i++)
            DeleteAnimation(&(animator->animations[i]));

        free(animator->animations);
        animator->animations = NULL;

        return true;
    }
    return false;
}

Vector2 ImageQuadAnimator(Animator* animator) {
    return (Vector2) {animator->image.width/animator->dimension.x, animator->image.height/animator->dimension.y};
}

void SetAnimationAnimator(Animator* animator, const char* name, bool flag) {
    animator->nameAnimation = name;
    FlipHImageAnimator(animator, flag);
    for (int i = 0; i < animator->numAnimations; i++) {
        if (strcmp(name, animator->animations[i].name) == 0) {
            animator->currentIndex = i;
            if (animator->_prevIndex != animator->currentIndex) {
                animator->animations[i].index = 0;
                animator->_prevIndex = animator->currentIndex;
            }
            break;
        }
    }
}

void DrawAnimator(Animator* animator, Vector2 position) {
    DrawAnimation(&(animator->animations[animator->currentIndex]), &(animator->texture), position, animator->_isLeft);
}

void FlipHImageAnimator(Animator* animator, bool isLeft) {
    if (animator->_isLeft != isLeft) {
        ImageFlipHorizontal(&animator->image);
        UnloadTexture(animator->texture);
        animator->texture = LoadTextureFromImage(animator->image);
    }
    animator->_isLeft = isLeft;
}

const char* GetNameAnimator(Animator* animator) {
    return animator->nameAnimation;
}