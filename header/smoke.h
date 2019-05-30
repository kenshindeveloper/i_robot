#if !defined(IPARTICLE_H)
#define IPARTICLE_H

#include "raylib.h"

typedef struct Particle {
    Vector2 position;
    Color color;
    float alpha;
    float size;
    float rotation;
    bool active;

}Particle;

typedef struct Smoke {
    Texture2D texture;
    Particle* particles;
    int num;

}Smoke;

Smoke NewSmoke(const char*, int);

void EventSmoke(Smoke*, Vector2, bool, bool);

void DrawSmoke(Smoke*);

void DeleteSmoke(Smoke*);

#endif //IPARTICLE_H