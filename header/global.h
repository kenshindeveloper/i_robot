#if !defined(IGLOBAL_H)
#define IGLOBAL_H

#include "raylib.h"

typedef struct Global {
    Camera2D camera;  

    Color ground;  
}Global;

Global NewGlobal();

#endif //IGLOBAL_H