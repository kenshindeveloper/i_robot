#if !defined(IPARTICLE_H)
#define IPARTICLE_H

#include "raylib.h"

typedef struct Particle {
    Vector2 position;
    Color color;
    float alpha;
    float size;
    float rotation;
    float angle;
    bool active;

}Particle;

#endif //IPARTICLE_H