#include "../header/grid.h"

Grid NewGrid(Vector2 size) {
    Grid grid;
    grid.position = (Vector2) {0, 0};
    grid.size = size;
    grid.color = RAYWHITE;

    return grid;
}

void DrawIGrid(Grid* grid) {
    grid->position = (Vector2) {0, 0};

    for (int i=0; i < grid->size.y; i++) {
        DrawLine(grid->position.x, grid->position.y, grid->position.x, 3660, grid->color);
        grid->position.x += 64;
    }
    
    grid->position = (Vector2) {0, 0};
    for (int j=0; j < grid->size.y; j++) {
        DrawLine(grid->position.x, grid->position.y, 3660, grid->position.y, grid->color);
        grid->position.y += 64;
    }
}