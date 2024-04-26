#ifndef __PLAYER
#define __PLAYER

#include "shapes.h"
#include "animation.h"

const int specialAbility[]=
{
    0, //None
    1,  //+1 health
    2  //+1 mana
};

struct Player
{
    int id;
    std::string name;

    int health, mana, speed;

    int special;

    SDL_Texture* texture = NULL;
    SDL_Rect rect;

    Animation idle, cast, hurt, die;
};

struct Cat
{
    int id;
    std::string name;
    int health, mana, speed;

    int special;
    int posX, posY;
};

bool loadPlayerData(Player playerData[], SDL_Renderer* gRenderer);

void selectPlayer(int id, Cat& cat, Player playerData[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

//void drawPlayer(Cat& cat, SDL_Renderer* gRenderer, Player playerData[]);



#endif // PLAYER
