#include "headers/button.h"

void loadButtonTexture(button& Button, SDL_Renderer* gRenderer)
{
//    Button.rect.w = 200;
//    Button.rect.h = 200;
//    Button.texture.loadFromFile(Button.path, gRenderer);
}

bool isMouseOn(button& Button, int& mouseX, int& mouseY)
{
    if(Button.type == "rectangle")
    {
        double w = Button.scaler * Button.rect.w;
        double h = Button.scaler * Button.rect.h;

        if((mouseX >= Button.posX - w / 2 && mouseX <= Button.posX + w / 2)
        &&(mouseY >= Button.posY - h / 2 && mouseY <= Button.posY + h / 2))
        return 1;
    }
    else
    if(Button.type == "circle")
    {
        long long dx = mouseX - Button.posX;
        long long dy = mouseY - Button.posY;

        double radious = Button.scaler * Button.rect.w / 2;

//        std::cout << dx * dx + dy * dy << " " << (radious * radious) << std::endl;

        if(dx * dx + dy * dy <= (radious * radious)) return 1;
        return 0;
    }
    return 0;
}
