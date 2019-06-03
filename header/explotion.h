/**
 * @file explotion.h
 * @author Franklin Morales (Kenshin Urashima)
 * @brief Definicion de la estructura y las funciones
 * necesarias para generacion de explosiones.
 * @version 0.1
 * @date 2019-06-02
 * 
 * @copyright Copyright (c) Franklin Morales (Kenshin Urashima) 2019
 * 
 */

#if !defined(IEXPLOTION_H)
#define IEXPLOTION_H

#include "particle.h"

/**
 * @struct Explotion
 * @brief Estructura que permite generar las explosiones.
 */
typedef struct Explotion {
    Texture2D texture; // < Textura de la particula.
    Particle *particles; // < Puntero (arreglo) a la estructura Particle.
    int numParticles; // < Numero de particulas que se almacenara en <b>particles</b>.
    int contParticles;

}Explotion;


/**
 * @brief Inicializa la estructura Explotion.
 * @param numParticles Define el numero de particula que se
 * alamacenaran en el atributo <b>particles</b>.
 * @return Explotion Retorna una estructura Explotion inicializada.
 */
Explotion NewExplotion(int numParticles);

/**
 * @brief Funcion encargarda de procesar los eventos.
 * @param explotion Puntero a una extrutura tipo Explotion.
 * @param position Posicion de la bala (estructura Bullet).
 * @param isLeft Direccion de la bala (estructura Bullet).
 * @return Nada.
 * @see Bullet
 */
bool EventExplotion(Explotion *explotion, Vector2 position, bool isLeft);

/**
 * @brief Funcion encargada de dibujar las particulas.
 * @param explotion Puntero a una extrutura tipo Explotion.
 * @return Nada.
 */
void DrawExplotion(Explotion *explotion);

/**
 * @brief Funcion encargada de liberar la memoria reservada.
 * @param explotion Puntero a una extrutura tipo Explotion.
 * @return Nada.
 */
void DeleteExplotion(Explotion *explotion);

#endif //IEXPLOTION_H