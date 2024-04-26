#ifndef __BUTTON
#define __BUTTON

#include "animation.h"
#include "music.h"
#include <string>

struct button
{
    std::string path, type;
    SDL_Rect rect;
    LTexture texture;

    int posX, posY;
    double scaler;

    bool mouseDownHere = 0, mouseUpHere = 0;

    SFX sound;

    void setRect(int x, int y, int w, int h)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void setPos(int x, int y)
    {
        posX = x;
        posY = y;
    }
};

void loadButtonTexture(button& Button, SDL_Renderer* gRenderer);
bool isMouseOn(button& Button, int& mouseX, int& mouseY);

#endif // __BUTTON
