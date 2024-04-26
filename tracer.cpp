#include "headers/tracer.h"

void loadTracer(LTexture& dot, std::string path, SDL_Renderer* gRenderer)
{
    dot.loadFromFile(path.c_str(), gRenderer);
}

void renderTrace(LTexture& dot, std::vector<Pos>& mPos, SDL_Renderer* gRenderer)
{
    int T = mPos.size();

    if(T == 0) return;

    SDL_Rect dotRect = {0, 0, 30, 30};

    for(Pos p : mPos)
    {
        dot.render(p.x, p.y, gRenderer, &dotRect, 1);
//        std::cout << p.x << " " << p.y << std::endl;
    }
//    std::cout << std::endl;
}
