#include "shapes.h"
#include <fstream>

bool loadShapeData(shape shapeData[], SDL_Renderer* gRenderer)
{
    bool success = 1;

    std::ifstream inFile;
    inFile.open("data/shapes.txt");

    if(!inFile)
     {
         std::cout << "Failed to load shape data!";
         success = 0;
         return success;
     }

    int Total;
    inFile >> Total;

    shapeData[0].codeName = Total;
    shapeData[0].codeCount = Total;

//    std::cout << shapeData[0].codeCount << std::endl;

    for(int i = 1; i <= Total; i++)
    {
        inFile >> shapeData[i].codeName >> shapeData[i].codeCount >> shapeData[i].maxAllowedDiff
         >> shapeData[i].shapeName
         >> shapeData[i].imgPath;

//         std::cout << shapeData[i].shapeName << std::endl;

        for(int j = 1; j <= shapeData[i].codeCount; j++)
            inFile >> shapeData[i].codes[j];

        shapeData[i].texture = IMG_LoadTexture(gRenderer, shapeData[i].imgPath.c_str());
        if(shapeData[i].texture == NULL)
        {
            std::cout << "Failed to load shape texture! SDL_image error: " << IMG_GetError();
            success = 0;
            return success;
        }

        shapeData[i].rect.w = 200;
        shapeData[i].rect.h = 200;
    }

    inFile.close();

    return success;
}

void destroyShapeTexture(shape shapeData[])
{
    int Total = shapeData[0].codeCount;
    for(int i = 1; i <= Total; i++)
    {
        SDL_DestroyTexture(shapeData[i].texture);
        shapeData[i].texture = NULL;
    }
}
