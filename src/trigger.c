#include "../header/trigger.h"

Trigger NewTrigger(Rectangle rectangle, Color color) {
    Trigger trigger = {0};
    trigger.rectangle = rectangle;
    trigger.color = color;

    return trigger;
}

void EventTrigger(Trigger* trigger, Vector2 position, bool isLeft, bool isJumping) {
    trigger->rectangle.x =  (isLeft)?(position.x + 48):(position.x + 128);
    trigger->rectangle.y = (isJumping)?(position.y + 92):(position.y + 98);
}

void DrawTrigger(Trigger* trigger) {
    DrawRectangleRec(trigger->rectangle, trigger->color);
}
