/**
 * @file animation.h
 * @author Franklin Morales
 * @brief Fichero donde se define la estructura Animation y las
 * funciones asociadas a dicha estructura.
 * @version 1.0
 * @date 2019-06-01
 * @code{.c}
 * int main() {
 *      Animation idle = NewAnimation("idle", 2);
 *      PushAnimation(&idle, (Rectangle) {0.0f, 0.0f, 64.0f, 64.0f});
 *      PushAnimation(&idle, (Rectangle) {0.0f, 0.0f, 64.0f, 64.0f});
 *      
 *      return EXIT_SUCCESS;
 * }
 * @endcode
 */

#if !defined(IANIMATION_H)
#define IANIMATION_H

#include "raylib.h"

/**
 * @struct Animation
 * @brief Estrutura que almacena las animaciones
 * 
 * Estructura base para la definicion de las animaciones, permite
 * almacenar los diferentes <b>frames</b> de una animacion dentro
 * de una estructura de tipo Rectangle, la cual esta definida por
 * {position_x, position_y, width, height}.
 * @code
 * int main() {
 *      Animation animation = {0};
 *      animation.name = "idle";
 *      animation.frames = NULL;     
 * 
 *      return EXIT_SUCCESS;
 * }
 * @encode
 */
typedef struct Animation {
    char* name; /** < Nombre de la animacion. */
    Rectangle* frames; /** < Arreglo de frames, tipo Rectangle. */
    int numFrames;  /** < Numeros de frames necesarios para la reserva de memoria. */
    int index; /** < Indice del frame actual. */
    float frameFPS; /** < Contador que permite el cambio de frames. */

}Animation;

/**
 * @brief Inicializa una estructura Animation y la retorna.
 * @param name Es una cadena de caracteres donde se almacenan el nombre de la animacion.
 * @param numFrames Es el numero de frames que contendra la estructura Animation.
 * @return Animation Retorna la estructura inicializada.
 */
Animation NewAnimation(char* name, int numFrames);

/**
 * @brief Agrega un frame a la estructura Animation.
 * @param animation Es un puntero a una estructura Animation.
 * @param frame Es una estructura de tipo Rectangle que representa las coordenadas
 * de una textura para renderizar.
 * @return bool Devuelve un valor booleano, si agrega correctamente el frame devuelve true,
 * en caso contrario retorna false.
 */
bool PushFrameAnimation(Animation* animation, Rectangle frame);

/**
 * @brief Libera la memoria reservada para la variable <b>frames</b>.
 * @param animation Es un puntero a una estructura Animation.
 * @return bool Devuelve true si se logra liberar la memoria reservada
 * para la variable <b>frames</b>.
 * @see Animation
 */
bool DeleteAnimation(Animation* animation);

/**
 * @brief Dibuja los frames en pantalla
 * @param animation Es un puntero a una estructura Animation.
 * @param texture Es un puntero a una textura.
 * @param position Es un parametro de tipo Vector2 donde se almacena la posicion
 * del la estructura Player.
 * @param isLeft Es un parametro de tipo booleano que tiene valor true si el player
 * mira hacia la derecha, y posee un valor de true si el player mira hacia la izquierda.
 * @see Animation
 * @see Player
 */
void DrawAnimation(Animation* animation, Texture2D* texture, Vector2 position, bool isLeft);

#endif //IANIMATION_H