#if !defined(IMAP_H)
#define IMAP_H

#include "raylib.h"

typedef struct Tile {
    int id;
    Rectangle rectangle;
    Vector2 size;
    Vector2 diff;
    struct Tile* prox;
    bool solid;
}Tile;

typedef struct TileMap {
    Tile* fkTile; 
    Vector2 position;
    struct TileMap* prox;
}TileMap;

typedef struct Map {
    const char* path;
    Image image;
    Texture2D texture;
    int quad;
    int** matrix;
    Vector2 size;
    Vector2 dimension;
    Tile* tiles;
    TileMap* tileMap;
}Map;


void _LoadTile(Tile**, int, Rectangle, Vector2, Vector2, bool);

void _InitPositionTile(Map*);

Tile* _GetTile(Map*, int);

Map NewMap(const char*, const char*, Vector2, Vector2);

void DeleteMap(Map*);

bool Split(Map*, int, char*);

int Len(char*);

bool ReadFileMap(Map*);

void DrawMap(Map*);

#endif //IMAP_H