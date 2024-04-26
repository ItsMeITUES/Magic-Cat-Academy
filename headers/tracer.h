#ifndef __TRACER
#define __TRACER

#include "recognizer.h"
#include "animation.h"

void loadTracer(LTexture& dot, std::string path, SDL_Renderer* gRenderer);

void renderTrace(LTexture& dot, std::vector<Pos>& mPos, SDL_Renderer* gRenderer);

#endif // __TRACER
