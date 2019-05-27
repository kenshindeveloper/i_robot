#if !defined(IGRID_H)
#define IGRID_H

#include "raylib.h"

typedef struct Grid {
    Vector2 size;
    Vector2 position;
    Color color;
}Grid;

Grid NewGrid(Vector2);

void DrawIGrid(Grid*);

#endif //IGRID_H