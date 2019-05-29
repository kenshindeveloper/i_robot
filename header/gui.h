#if !defined(IGUI_H)
#define IGUI_H

#include "raylib.h"

//----------------------------------------------------------------------------------
// ImgGUI Definition
//----------------------------------------------------------------------------------

typedef struct ImgGUI {
    Image image;
    Texture2D texture;
    Rectangle rectangle;
    Vector2 position;
    Color color;
    bool isResize;

}ImgGUI;


ImgGUI NewImgGUI(const char*, Vector2, bool);

void EventImgGUI(ImgGUI*);

void DrawImgGUI(ImgGUI*);

void DeleteImgGUI(ImgGUI*);

//----------------------------------------------------------------------------------
// Power Definition
//----------------------------------------------------------------------------------

typedef struct Power {
    ImgGUI background;
    ImgGUI full;

}Power;

Power NewPower();

void EventPower(Power*);

void DrawPower(Power*);

void DeletePower(Power*);

//----------------------------------------------------------------------------------
// Gui Definition
//----------------------------------------------------------------------------------

typedef struct Gui {
    Rectangle rectangle;
    Color color;
    Power power;
}Gui;

Gui NewGui(Rectangle, Color);

void EventGui(Gui*);

void DrawGui(Gui*);

void DeleteGui(Gui*);

#endif //IGUI_H