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
    Texture2D texture;
    int quad;
    int** matrix;
    Vector2 size;
    Vector2 dimension;
    Tile* tiles;
}Map;

void _LoadTile(Tile**, int, Rectangle);

Tile* _GetTile(Map*, int);

Map NewMap(const char*, const char*, Vector2, Vector2);

void DeleteMap(Map*);

bool Split(Map*, int, char*);

int Len(char*);

bool ReadFileMap(Map*);

void DrawMap(Map*);

#endif //IMAP_H