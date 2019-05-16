#if !defined(IMAP_H)
#define IMAP_H

#include "raylib.h"

typedef struct Tile {
    int id;
    Rectangle rectangle;
    struct Tile* prox;
}Tile;

typedef struct Map {
    const char* path;
    Image image;
    Texture texture;
    int** matrix;
    Vector2 size;
    Tile* tiles;
}Map;

void _LoadTile(Tile**, int, Rectangle);

Map NewMap(const char*, Vector2);

void DeleteMap(Map*);

void Split(Map*, int, char*);

int Len(char*);

bool ReadFileMap(Map*);

#endif //IMAP_H