#include "../header/shape.h"

Shape NewShape(Vector2 position, Vector2 size, Color color) {
    Shape shape;
    shape.position = position;
    shape.size = size;
    shape.color = color;

    return shape;
}
 
void SetPositionShape(Shape* shape, Vector2 position) {
    shape->position = position;
}

void DrawShape(Shape* shape) {
    DrawRectangle(shape->position.x, shape->position.y, shape->size.x, shape->size.y, shape->color);
}