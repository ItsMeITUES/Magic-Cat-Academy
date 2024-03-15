#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int inf = 1e9;
const int maxDrawWays = 5;
const int shapeNum = 20;

struct shapes
{
    short codeName, codeCount, maxDiff;
    std::string shapeName, imgPath;
    std::string codes[maxDrawWays];
    SDL_Texture* texture = NULL;
};

bool loadShapeData(shapes Gesture[], SDL_Renderer* gRenderer);
void destroyShapeTexture(shapes Gesture[]);
