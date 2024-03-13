#include "shapes.h"
#include <fstream>

bool loadShapeData(shapes Gesture[])
{
    bool success = 1;

    std::ifstream inFile;
    inFile.open("shapes.txt");

    if(!inFile) success = 0;

    int Total;
    inFile >> Total;

    Gesture[0].codeName = Total;
    Gesture[0].codeCount = Total;

    for(int i = 1; i <= Total; i++)
    {
        inFile >> Gesture[i].codeName >> Gesture[i].codeCount
         >> Gesture[i].shapeName
         >> Gesture[i].imgPath;

         if(!inFile)
         {
             std::cout << "Failed to load shape data!";
             success = 0;
         }

        for(int j = 1; j <= Gesture[i].codeCount; j++)
            inFile >> Gesture[i].codes[j];

//        Gesture[i].texture = IMG_LoadTexture(gRenderer, Gesture[i].imgPath.c_str());
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
