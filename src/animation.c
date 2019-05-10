#include <stdio.h>
#include <stdlib.h>
#include "../header/animation.h"
#include "../header/config.h"

extern Config config;

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

void DrawAnimation(Animation* animation, Texture2D* texture, Vector2 position, bool isLeft) {
    if (animation->frameFPS > (config.fps/6)) {
        animation->index++;
        animation->frameFPS = 0;

        if (animation->index >= animation->numFrames)
            animation->index = 0;
    }

    if (!isLeft) {
        Rectangle frame = animation->frames[animation->index];
        float pos = 0;
        if (frame.x == 0)
            pos = texture->width-frame.width;
        else if (frame.x == frame.width)
            pos = texture->width-frame.width*2;
        else if (frame.x == frame.width*2)
            pos = texture->width-frame.width*3;
        else if (frame.x == frame.width*3)
            pos = texture->width-frame.width*4;

        Rectangle auxRect = (Rectangle) {pos, frame.y, frame.width, frame.height};
        DrawTextureRec((*texture), auxRect, position, WHITE);
    }
    else {
        DrawTextureRec((*texture), animation->frames[animation->index], position, WHITE);
    }

    animation->frameFPS++;
}