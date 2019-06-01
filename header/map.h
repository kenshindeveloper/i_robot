#if !defined(IMAP_H)
#define IMAP_H

#include "raylib.h"

/**
 *  estructura: Tile
 *  permite almacenar el tile
 *  unico para el renderizado.
 * **/
typedef struct Tile {
    int id; //  id representa el numero unico por Tile.
    Rectangle rectangle;
    Vector2 size; //  tamano (x, y) del shape colision. 
    Vector2 diff; //  diferencia en x, y para el shape de la colision.
    struct Tile* prox;
    bool solid;
}Tile;

/**
 *  estructura: TileMap
 *  permite almacenar la relacion de un Tile con una 
 *  posicion, el tile es un puntero a una estructura tipo
 *  Tile.
 **/
typedef struct TileMap {
    Tile* fkTile; 
    Vector2 position;
    struct TileMap* prox;
}TileMap;

/**
 *  estructura: Map
 *  guarda la informacion del TilSet que se carga,
 *  representa el mapa y contiene la informacion 
 *  relacionada.
 * **/
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