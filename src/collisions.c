#include <stdlib.h>
#include "../header/collisions.h"

/**
 *  funcion: AddCollisions
 *  reserva la memoria necesaria para el
 *  almacenamiento de la estructura Rectangle.
 * **/
void AddCollisions(Collisions** collisions, Rectangle rectangle) {
    if ((*collisions) == NULL) {
        (*collisions) = (Collisions*) malloc(sizeof(Collisions));
        (*collisions)->rectangle = rectangle;
        (*collisions)->prox = NULL;
    }
    else {
        Collisions* auxCollision = (*collisions);
        while (auxCollision->prox != NULL) auxCollision = auxCollision->prox;

        auxCollision->prox = (Collisions*) malloc(sizeof(Collisions));
        auxCollision->prox->rectangle = rectangle;
        auxCollision->prox->prox = NULL;
    }
}

/**
 *  funcion: DeleteCollisions
 *  libera la memoria reservada.
 * **/
void DeleteCollisions(Collisions** collisions) {
    Collisions* auxCollisions = NULL;

    while ((*collisions) != NULL) {
        auxCollisions = (*collisions);
        (*collisions) = (*collisions)->prox;
        free(auxCollisions);
        auxCollisions = NULL;
    }
}

/**
 *  funcion: CheckCollisions
 *  retorna un valor booleano si hubo o no
 *  colision entre los Rectangles.
 * **/
bool CheckCollisions(Collisions* collisions, Rectangle* rectangle) {
    while (collisions != NULL) {
        if (CheckCollisionRecs(collisions->rectangle, *rectangle))
            return true;
        collisions = collisions->prox;
    }

    return false;
}