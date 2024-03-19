#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int inf = 1e9;
const int maxDrawWays = 5;
const int shapeNum = 20;

struct shape
{
    short codeName, codeCount, maxAllowedDiff;
    std::string shapeName, imgPath;
    std::string codes[maxDrawWays];
    SDL_Texture* texture = NULL;
    SDL_Rect rect;
};

bool loadShapeData(shape shapeData[], SDL_Renderer* gRenderer);
void destroyShapeTexture(shape shapeData[]);
