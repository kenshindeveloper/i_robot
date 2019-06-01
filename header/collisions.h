#if !defined(ICOLLISIONS_H)
#define ICOLLISIONS_H

#include "raylib.h"
/**
 *  Estructura que permite almacenar todos
 * las estructuras tipo Rectangle para 
 * evaluar la colision de los objetos.
 * **/
typedef struct Collisions {
    Rectangle rectangle;
    struct Collisions* prox;

}Collisions;

/**
 *  funcion: AddCollisions
 *  agrega una structura de tipo Rectangle en
 *  la estructura Collisions.
 * **/
void AddCollisions(Collisions**, Rectangle);

/**
 * funcion: DeleteCollisions
 * **/
void DeleteCollisions(Collisions**);

/**
 *  funcion: CheckCollisions 
 *  evalua la colision entre dos Rectangle, 
 *  si existe una colision devuelve true, 
 *  de lo contrario retorna false.
 * **/
bool CheckCollisions(Collisions*, Rectangle*);

#endif //ICOLLISIONS_H