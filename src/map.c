#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/map.h"

void _LoadTile(Tile** tile, int id, Rectangle rectangle) {
    if ((*tile) == NULL) {
        (*tile) = (Tile*) malloc(sizeof(Tile));
        (*tile)->id = id;
        (*tile)->rectangle = rectangle;
        (*tile)->prox = NULL;
    }
    else {
        Tile* auxTile = (*tile);
        while (auxTile->prox != NULL)
            auxTile = auxTile->prox;
        
        auxTile->prox = (Tile*) malloc(sizeof(Tile));
        auxTile->prox->id = id;
        auxTile->prox->rectangle = rectangle;
        auxTile->prox->prox = NULL;
    }
}

Tile* _GetTile(Map* map, int id) {
    Tile* result = map->tiles;

    while (result != NULL && result->id != id) {
        result = result->prox;
    }

    return result;
}

Map NewMap(const char* path, const char* pathImage, Vector2 size, Vector2 dimension) {
    Map map;
    map.path = path;
    map.image = LoadImage(pathImage);
    map.texture = LoadTextureFromImage(map.image);
    map.size = size;
    map.tiles = NULL;
    map.matrix = (int**) calloc(size.y, sizeof(int));
    map.dimension = dimension;
    for (int i = 0; i < map.size.y; i++)
        map.matrix[i] = (int*) calloc(size.x, sizeof(int));

    ReadFileMap(&map);

    for (int i=0; i < map.size.y; i++) {
        for (int j=0; j < map.size.x; j++)
            printf("%d ", map.matrix[i][j]);
        printf("\n"); 
    }

    //Carga los tiles
    map.quad = (int) (map.image.width / map.dimension.x);
    // Load first row
    _LoadTile(&map.tiles, 0, (Rectangle) {0, 0, map.quad, map.quad});
    _LoadTile(&map.tiles, 1, (Rectangle) {map.quad, 0,map.quad,map.quad});
    _LoadTile(&map.tiles, 2, (Rectangle) {map.quad*2, 0,map.quad,map.quad});

    _LoadTile(&map.tiles, 3, (Rectangle) {0,map.quad,map.quad,map.quad});
    _LoadTile(&map.tiles, 4, (Rectangle) {map.quad,map.quad,map.quad,map.quad});
    _LoadTile(&map.tiles, 5, (Rectangle) {map.quad*2,map.quad,map.quad,map.quad});

    _LoadTile(&map.tiles, 6, (Rectangle) {0,map.quad*2,map.quad,map.quad});
    _LoadTile(&map.tiles, 7, (Rectangle) {map.quad,map.quad*2,map.quad,map.quad});
    _LoadTile(&map.tiles, 8, (Rectangle) {map.quad*2,map.quad*2,map.quad,map.quad});

    _LoadTile(&map.tiles, 9, (Rectangle) {0,map.quad*3,map.quad,map.quad});
    _LoadTile(&map.tiles, 10, (Rectangle) {map.quad,map.quad*3,map.quad,map.quad});
    _LoadTile(&map.tiles, 11, (Rectangle) {map.quad*2,map.quad*3,map.quad,map.quad});

    _LoadTile(&map.tiles, 12, (Rectangle) {0,map.quad*4,map.quad,map.quad});
    _LoadTile(&map.tiles, 13, (Rectangle) {map.quad,map.quad*4,map.quad,map.quad});
    _LoadTile(&map.tiles, 14, (Rectangle) {map.quad*2,map.quad*4,map.quad,map.quad});

    _LoadTile(&map.tiles, 15, (Rectangle) {0,map.quad*5,map.quad,map.quad});
    _LoadTile(&map.tiles, 16, (Rectangle) {map.quad,map.quad*5,map.quad,map.quad});
    // _LoadTile(&map.tiles, 15, (Rectangle) {quad*2,map.quad*4,map.quad,map.quad});

    return map;
}

void DeleteMap(Map* map) {
    if (map->tiles != NULL) {
        Tile* auxTile = NULL;
        while (map->tiles != NULL) {
            auxTile = map->tiles;
            map->tiles = map->tiles->prox;
            free(auxTile);
            auxTile = NULL;
        }

        if (map->tiles != NULL) {
            free(map->tiles);
            map->tiles = NULL;
        }
    }

    if (map->matrix != NULL) {
        for (int i = 0; i < map->size.y; i++) {
            free(map->matrix[i]);
            map->matrix[i] = NULL;
        }
        free(map->matrix);
        map->matrix = NULL;
    }
}

bool ReadFileMap(Map* map) {
    FILE* file = fopen(map->path, "r+");
    if (file == NULL) 
        return false;

    char* string = (char*) calloc(128, sizeof(char));
    int index = 0;
    while (feof(file) == 0 && index < map->size.y) {
        fgets(string, 128, file);
        Split(map, index, string); 
        index++;
    }
    free(string);
    fclose(file);
    file = NULL;

    return true;
}

void Split(Map* map, int rowIndex, char* string) {
    int index = 0;
    int value = 0;
    int mult = 1; 
    for (int i = 0; i < strlen(string); i++) {
        if ((string[i] >= 48 && string[i] <= 57) || string[i] == '-') {
            if (string[i] == '-') {
                value = -1;
            }
            else {
                if (value < 0)
                    value = ((int) string[i] - '0') * mult * (-1);
                else
                    value += ((int) string[i] - '0') * mult;
                mult *= 10;
            }
        }         
        else if (string[i] == ',' || string[i] == '\n') {
            map->matrix[rowIndex][index++] = value;
            value = 0;
            mult = 1;
        }
    }
}

int Len(char* string) {
    int size = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ',')
            size++;
    }
    return (size > 0)?(size+1):(0);
}

void DrawMap(Map* map) {
    Tile* auxTile = map->tiles;
    Vector2 position = (Vector2) {0, 0};

    for (int i=0; i < map->size.y; i++) {
        for (int j=0; j < map->size.x; j++) {
            auxTile = _GetTile(map, map->matrix[i][j]);
            if (auxTile != NULL)
                DrawTextureRec(map->texture, auxTile->rectangle, position, WHITE);
            
            position.x += map->quad;
        }
        position.x = 0;
        position.y += map->quad;
    }
}