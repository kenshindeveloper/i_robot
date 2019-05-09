#include <stdlib.h>
#include "../header/animation.h"

Animation NewAnimation(char* name, int numFrames) {
    Animation animation;
    animation.name = name;
    animation.numFrames = numFrames;
    animation.frames = (Rectangle*) malloc(sizeof(Rectangle)*numFrames);
    animation.index = 0;
    animation.frameFPS = 0.0f;

    return animation;
}


bool PushFrameAnimation(Animation* animation, Rectangle frame) {
    if (animation->index < animation->numFrames) {
        animation->frames[animation->index++] = frame; //asigna el frame y aumenta el index.

        return true;
    }
    return false;
}

bool DeleteAnimation(Animation* animation) {
    if (animation->frames != NULL) {
        free(animation->frames);    
        animation->frames = NULL;

        return true;
    }
    return false;
}

void DrawAnimation(Animation* animation, Texture2D* texture, Vector2 position) {
    if (animation->frameFPS > (60/9)) {
        animation->index++;
        animation->frameFPS = 0;

        if (animation->index >= animation->numFrames)
            animation->index = 0;
    }
    DrawTextureRec((*texture), animation->frames[animation->index], position, WHITE);
    animation->frameFPS++;
}