#include "animation.h"
#include <SDL_image.h>

void loadAnimation(Animation& ani, SDL_Renderer* gRenderer)
{
    std::string path = ani.path;
    if(!ani.sheetTexture.loadFromFile(path, gRenderer))
    {
        return;
    }

    for(int i = 0; i < ani.frameCount; i++)
    {
        SDL_Rect framePos;
        framePos.x = (i % ani.spritePerRow) * ani.frameSize.w;
        framePos.y = (i / ani.spritePerRow) * ani.frameSize.h;
        framePos.w = ani.frameSize.w;
        framePos.h = ani.frameSize.h;

        std::cout << framePos.x << " " << framePos.y << std::endl;

        ani.clips.push_back(framePos);
    }
}

void playAnimation(Animation& ani, SDL_Renderer* gRenderer)
{
    SDL_Rect* currentFrame = &ani.clips[ani.frameIndex / 6];
    ani.sheetTexture.render(ani.frameSize.x, ani.frameSize.y, gRenderer, currentFrame);
    ani.frameIndex++;

    if(ani.frameIndex / 6 >= ani.frameCount) ani.frameIndex = 0;
}
