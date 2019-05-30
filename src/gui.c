#include "../header/gui.h"
#include "../header/config.h"
#include "../header/global.h"

extern Config config;
extern Global global;

//----------------------------------------------------------------------------------
// ImgGUI Implementation
//----------------------------------------------------------------------------------

ImgGUI NewImgGUI(const char* path, Vector2 position, bool isResize) {
    ImgGUI imgGui = {0};

    imgGui.image = LoadImage(path);
    ImageResizeNN(&imgGui.image, imgGui.image.width/2, imgGui.image.height/2);
    imgGui.texture = LoadTextureFromImage(imgGui.image);
    imgGui.rectangle = (Rectangle) {0, 0, imgGui.image.width, imgGui.image.height};
    imgGui.position = position;
    imgGui.isResize = isResize;

    return imgGui;
}

void EventImgGUI(ImgGUI* imgGui) {
    
}

void DrawImgGUI(ImgGUI* imgGui) {
    if (imgGui->isResize) {
        Rectangle rect = (Rectangle) {imgGui->rectangle.x, imgGui->rectangle.y, (imgGui->rectangle.width*global.power)/100, imgGui->rectangle.height};
        DrawTextureRec(imgGui->texture, rect, imgGui->position, WHITE);
    }
    else {
        DrawTextureRec(imgGui->texture, imgGui->rectangle, imgGui->position, WHITE);
    }
}

void DeleteImgGUI(ImgGUI* imgGui) {
    UnloadImage(imgGui->image);
}


//----------------------------------------------------------------------------------
// Power Implementation
//----------------------------------------------------------------------------------

Power NewPower() {
    Power power = {0};
    power.background = NewImgGUI("resources/sprites/power_base.png", (Vector2) {config.screenWidth-150, -2}, false);
    power.full = NewImgGUI("resources/sprites/power_full.png", (Vector2) {config.screenWidth-150, -2}, true);

    return power;
}

void EventPower(Power* power) {
    EventImgGUI(&power->background);
    EventImgGUI(&power->full);
}

void DrawPower(Power* power) {
    DrawImgGUI(&power->background);
    DrawImgGUI(&power->full);
}

void DeletePower(Power* power) {
    DeleteImgGUI(&power->background);
    DeleteImgGUI(&power->full);
}

//----------------------------------------------------------------------------------
// Gui Implementation
//----------------------------------------------------------------------------------

Gui NewGui(Rectangle rectangle, Color color) {
    Gui gui = {0};
    gui.rectangle = rectangle;
    gui.color = color;
    gui.power = NewPower();

    return gui;
}

void EventGui(Gui* gui) {
    EventPower(&gui->power);
}

void DrawGui(Gui* gui) {
    DrawRectangleRec(gui->rectangle, gui->color);
    DrawPower(&gui->power);
}

void DeleteGui(Gui* gui) {
    DeletePower(&gui->power);
}