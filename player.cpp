#include "player.h"
#include "animation.h"
#include <fstream>

bool loadPlayerData(Player playerData[], SDL_Renderer* gRenderer)
{
    bool success = 1;

    std::ifstream inFile;
    inFile.open("data/player.txt");

    if(!inFile)
     {
         std::cout << "Failed to load player data!";
         success = 0;
         return success;
     }

    int Total;
    inFile >> Total;

    playerData[0].id = Total;

//    std::cout << playerData[0].codeCount << std::endl;

    for(int i = 1; i <= Total; i++)
    {
        inFile >> playerData[i].id >> playerData[i].name
        >> playerData[i].health >> playerData[i].mana
        >> playerData[i].speed;

        inFile >> playerData[i].special;

        std::string path;
        inFile >> path;

        playerData[i].texture = IMG_LoadTexture(gRenderer, path.c_str());
        if(playerData[i].texture == NULL)
        {
            std::cout << "Failed to load player texture! SDL_image error: " << IMG_GetError();
            success = 0;
            return success;
        }

        inFile >> playerData[i].rect.w;
        inFile >> playerData[i].rect.h;
    }

    Animation test;
    test.path = "animation/blackCat/blackCat_idle.png";
    test.spritePerRow = 5;
    test.frameCount = 25;
    test.frameSize.w = 208;
    test.frameSize.h = 188;

    loadAnimation(test, gRenderer);

    playerData[1].anim = test;

    inFile.close();

    return success;
}

void selectPlayer(int id, Cat& cat, Player playerData[], const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    cat.id = playerData[id].id;
    cat.name = playerData[id].name;

    cat.health = playerData[id].health;
    cat.mana = playerData[id].mana;
    cat.speed = playerData[id].speed;

    cat.special = playerData[id].special;
    cat.posX = 200;
    cat.posY = SCREEN_HEIGHT / 2;

    playerData[id].anim.frameSize.x = cat.posX - playerData[id].anim.frameSize.w / 2;
    playerData[id].anim.frameSize.y = cat.posY - playerData[id].anim.frameSize.h / 2;
}

//void drawPlayer(Cat& cat, SDL_Renderer* gRenderer, Player playerData[])
//{
//    SDL_Rect rect = playerData[cat.id].rect;
//
//    double scaler = 0.5;
//
//    rect.w *= scaler;
//    rect.h *= scaler;
//    rect.x = cat.posX - rect.w / 2;
//    rect.y = cat.posY - rect.h / 2;
//
//    SDL_RenderCopy(gRenderer, playerData[cat.id].texture, NULL, &rect);
//}

