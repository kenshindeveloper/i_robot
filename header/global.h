#if !defined(IGLOBAL_H)
#define IGLOBAL_H

#include "raylib.h"
#include "grid.h"

typedef struct Global {
    Camera2D camera;  
    int valueMinTile;
    Color groundColor;  
    Color background;

    bool isViewGrid;
    bool isViewShape;
    Grid grid;

}Global;

Global NewGlobal();

void EventGlobal(Global*);

void DrawGlobal(Global*);

#endif //IGLOBAL_H