#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/map.h"
#include "../header/global.h"
#include "../header/collisions.h"

extern Global global;
extern Collisions* collisions;

void _LoadTile(Tile** tile, int id, Rectangle rectangle, Vector2 size, Vector2 diff, bool solid) {
    if ((*tile) == NULL) {
        (*tile) = (Tile*) malloc(sizeof(Tile));
        (*tile)->id = id;
        (*tile)->rectangle = rectangle;
        (*tile)->size = size;
        (*tile)->diff = diff;
        (*tile)->solid = solid;
        (*tile)->prox = NULL;
    }
    else {
        Tile* auxTile = (*tile);
        while (auxTile->prox != NULL)
            auxTile = auxTile->prox;
        
        auxTile->prox = (Tile*) malloc(sizeof(Tile));
        auxTile->prox->id = id;
        auxTile->prox->rectangle = rectangle;
        auxTile->prox->size = size;
        auxTile->prox->diff = diff;
        auxTile->prox->solid = solid;
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
    map.tileMap = NULL;
    for (int i = 0; i < map.size.y; i++)
        map.matrix[i] = (int*) calloc(size.x, sizeof(int));

    ReadFileMap(&map);

    //Carga los tiles
    map.quad = (int) (map.image.width / map.dimension.x);
    // Load first row
    _LoadTile(&map.tiles, -1, (Rectangle) {0, 0, 0, 0}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);
    _LoadTile(&map.tiles, 0, (Rectangle) {0, 0, map.quad, map.quad}, (Vector2) {map.quad, map.quad-18}, (Vector2) {0, 18}, true);
    _LoadTile(&map.tiles, 1, (Rectangle) {map.quad, 0, map.quad, map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);
    _LoadTile(&map.tiles, 2, (Rectangle) {map.quad*2, 0, map.quad, map.quad}, (Vector2) {map.quad, map.quad-18}, (Vector2) {0, 18}, true);

    _LoadTile(&map.tiles, 3, (Rectangle) {0, map.quad, map.quad, map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 4, (Rectangle) {map.quad, map.quad, map.quad, map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 5, (Rectangle) {map.quad*2,map.quad,map.quad,map.quad}, (Vector2) {map.quad, map.quad-18}, (Vector2) {0, 18}, true);

    _LoadTile(&map.tiles, 6, (Rectangle) {0,map.quad*2,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 7, (Rectangle) {map.quad,map.quad*2,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 8, (Rectangle) {map.quad*2,map.quad*2,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);

    _LoadTile(&map.tiles, 9, (Rectangle) {0,map.quad*3,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 10, (Rectangle) {map.quad,map.quad*3,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 11, (Rectangle) {map.quad*2,map.quad*3,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);

    _LoadTile(&map.tiles, 12, (Rectangle) {0,map.quad*4,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, true);
    _LoadTile(&map.tiles, 13, (Rectangle) {map.quad,map.quad*4,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);
    _LoadTile(&map.tiles, 14, (Rectangle) {map.quad*2,map.quad*4,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);

    _LoadTile(&map.tiles, 15, (Rectangle) {0,map.quad*5,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);
    _LoadTile(&map.tiles, 16, (Rectangle) {map.quad,map.quad*5,map.quad,map.quad}, (Vector2) {map.quad, map.quad}, (Vector2) {0, 0}, false);
    // _LoadTile(&map.tiles, 15, (Rectangle) {quad*2,map.quad*4,map.quad,map.quad});
    _InitPositionTile(&map);

    return map;
}

void _InitPositionTile(Map* map) {
    Vector2 position = (Vector2) {0, 0};

    for (int i=0; i < map->size.y; i++) {
        for (int j=0; j < map->size.x; j++) {
            if ((map->matrix[i][j] >= 0) && (map->tileMap == NULL)) {
                map->tileMap = (TileMap*) malloc(sizeof(TileMap));
                map->tileMap->fkTile = _GetTile(map, map->matrix[i][j]);
                map->tileMap->position = position;
                map->tileMap->prox = NULL;
                AddCollisions(
                    &collisions, 
                    (Rectangle) {
                        position.x, 
                        position.y, 
                        map->tileMap->fkTile->size.x,
                        map->tileMap->fkTile->size.y
                    }
                );
            }
            else if (map->matrix[i][j] >= 0) {
                TileMap* auxTileMap = map->tileMap;
                while (auxTileMap->prox != NULL)
                    auxTileMap = auxTileMap->prox;

                auxTileMap->prox = (TileMap*) malloc(sizeof(TileMap));
                auxTileMap->prox->fkTile = _GetTile(map, map->matrix[i][j]);
                auxTileMap->prox->position = position;
                auxTileMap->prox->prox = NULL;

                AddCollisions(
                    &collisions, 
                    (Rectangle) {
                        position.x, 
                        position.y, 
                        auxTileMap->prox->fkTile->size.x,
                        auxTileMap->prox->fkTile->size.y
                    }
                );
            }
            position.x += map->quad;
        }
        position.x = 0;
        position.y += map->quad;
    }
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
    }

    if (map->tileMap != NULL) {
        TileMap* auxTileMap = NULL;
        while (map->tileMap != NULL) {
            auxTileMap = map->tileMap;
            map->tileMap = map->tileMap->prox;
            free(auxTileMap);
            auxTileMap = NULL;    
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

    char* string = (char*) calloc(512, sizeof(char));
    int index = 0;
    while (feof(file) == 0 && index < map->size.y) {
        fgets(string, 512, file);
        Split(map, index, string); 
        index++;
    }
    free(string);
    fclose(file);
    file = NULL;

    return true;
}

bool Split(Map* map, int rowIndex, char* string) {
    char* data = NULL;
	int size = 0;
	int i = 0;
	int index = 0;

	while (string[i] != '\0') {
		if ((string[i] >= 48 && string[i] <= 57) || string[i] == '-') {
			size += 1;

			if (data == NULL)
				data = (char*) calloc(size, sizeof(char));
			else {
				char* auxData = (char*) realloc(data, size);
				if (auxData == NULL) 
					return false;
				
				data = auxData;
			}

			data[size-1] = string[i];	
		}
		else if (string[i] == '\n' || string[i] == ',') {
			map->matrix[rowIndex][index++] = atoi(data);
			size = 0;

			if (data != NULL) {
				free(data);
				data = NULL;
			}
		}
		i++;
	}

    if (data != NULL) {
		map->matrix[rowIndex][index++] = atoi(data);
		free(data);
		data = NULL;
	}
	
	return true;
}

int Len(char* string) {
    int len = 0;
	int index = 0;
	while (string[index] != '\0') {
		if (string[index++] == ',')
			len++;
	}
	return len;
}

void DrawMap(Map* map) {
    TileMap* auxTileMap = map->tileMap;

    while(auxTileMap != NULL) {
        DrawTextureRec(map->texture, auxTileMap->fkTile->rectangle, auxTileMap->position, WHITE);
        
        if (global.isViewShape && auxTileMap->fkTile->solid)
            DrawRectangle(
                auxTileMap->position.x+auxTileMap->fkTile->diff.x, 
                auxTileMap->position.y+auxTileMap->fkTile->diff.y, 
                auxTileMap->fkTile->size.x, 
                auxTileMap->fkTile->size.y, 
                global.groundColor
            );

        auxTileMap = auxTileMap->prox;
    }
}