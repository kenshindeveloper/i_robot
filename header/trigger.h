#if !defined(ITRIGGER_H)
#define ITRIGGER_H

#include "raylib.h"

typedef struct Trigger {
    Rectangle rectangle;
    Color color;
}Trigger;

Trigger NewTrigger(Rectangle, Color);

void EventTrigger(Trigger*, Vector2, bool, bool);

void DrawTrigger(Trigger*);

#endif //ITRIGGER_H