#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/map.h"

void _LoadTile(Tile** tile, int id, Rectangle rect) {
    if (tile == NULL) {
    }
    else {
    }
}

Map NewMap(const char* path, Vector2 size) {
    Map map;
    map.path = path;
    map.image = LoadImage(path);
    map.texture = LoadTextureFromImage(map.image);
    map.size = size;
    map.tiles = NULL;
    map.matrix = (int**) calloc(size.y, sizeof(int));
    for (int i = 0; i < map.size.y; i++)
        map.matrix[i] = (int*) calloc(size.x, sizeof(int));

    return map;
}

void DeleteMap(Map* map) {
    if (map->tiles != NULL) {
        free(map->tiles);
        map->tiles = NULL;
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
        printf("%s", string);
        Split(map, index, string); 
        index++;
    }
    printf("index: %d\n", index);
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