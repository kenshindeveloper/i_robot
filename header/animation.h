#if !defined(IANIMATION_H)
#define IANIMATION_H

#include "raylib.h"

typedef struct Animation {
    char* name;
    Rectangle* frames;
    int numFrames;
    int index;

    float frameFPS;
}Animation;

Animation NewAnimation(char*, int);

bool PushFrameAnimation(Animation*, Rectangle);

bool DeleteAnimation(Animation*);

void DrawAnimation(Animation*, Texture2D*, Vector2, bool);

#endif //IANIMATION_H