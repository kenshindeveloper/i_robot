#if !defined(ISHAPE_H)
#define ISHAPE_H

#include "raylib.h"

typedef struct Shape {
    Vector2 position;
    Vector2 size;
    Color color;

}Shape;

Shape NewShape(Vector2, Vector2, Color);

void SetPositionShape(Shape*, Vector2);

void DrawShape(Shape*);

#endif //ISHAPE_H