#include "shapes.h"
#include <fstream>

bool loadShapeData(shapes Gesture[], SDL_Renderer* gRenderer)
{
    bool success = 1;

    std::ifstream inFile;
    inFile.open("shapes.txt");

    if(!inFile)
     {
         std::cout << "Failed to load shape data!";
         success = 0;
         return success;
     }

    int Total;
    inFile >> Total;

    Gesture[0].codeName = Total;
    Gesture[0].codeCount = Total;

    for(int i = 1; i <= Total; i++)
    {
        inFile >> Gesture[i].codeName >> Gesture[i].codeCount >> Gesture[i].maxDiff
         >> Gesture[i].shapeName
         >> Gesture[i].imgPath;

        for(int j = 1; j <= Gesture[i].codeCount; j++)
            inFile >> Gesture[i].codes[j];

        Gesture[i].texture = IMG_LoadTexture(gRenderer, Gesture[i].imgPath.c_str());
        if(Gesture[i].texture == NULL)
        {
            std::cout << "Failed to load shape texture! SDL_image error: " << IMG_GetError();
            success = 0;
            return success;
        }
    }

    inFile.close();

    return success;
}

void destroyShapeTexture(shapes Gesture[])
{
    int Total = Gesture[0].codeCount;
    for(int i = 1; i <= Total; i++)
    {
        SDL_DestroyTexture(Gesture[i].texture);
        Gesture[i].texture = NULL;
    }
}
