#include "shapes.h"
#include "recognizer.h"
#include "comparer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const std::string SCREEN_TITLE = "Magic Cat Academy";

const int fps = 60;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL;
SDL_Texture* button = NULL;

shapes Gesture[shapeNum];

bool isMouseDown = 0;

bool init()
{
    bool success = 1;

    if((SDL_Init(SDL_INIT_VIDEO) < 0))
    {
        std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError();
        success = 0;
    }
    else
    {
        gWindow = SDL_CreateWindow("Magic Cat Academy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std::cout << "Cannot create Window! SDL Error: " << SDL_GetError();
            success = 0;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                std::cout << "Cannot create Renderer! SDL Error: " << SDL_GetError();
                success = 0;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags))
                {
                    std::cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError();
                    success = 0;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = 1;

    gTexture = IMG_LoadTexture(gRenderer, "images/Testing.png");
    if(gTexture == NULL) exit(0);

    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

    return success;
}

void loadShape(int& shapeCodeName, shapes Gesture[])
{
    std::string path = Gesture[shapeCodeName].imgPath;

    SDL_Texture* shapeTexture = Gesture[shapeCodeName].texture;

    if(shapeTexture == NULL)
    {
        std::cout << "Unable to load texture!";
        return;
    }

    button = shapeTexture;
}

void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyTexture(button);
    button = NULL;

    destroyShapeTexture(Gesture);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Pos> mousePos;
std::string answer = "-1";

void handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        isMouseDown = 1;
    }

    if(e->type == SDL_MOUSEBUTTONUP)
    {
        isMouseDown = 0;
        processMouseMovement(mousePos, answer);

        shortenAnswer(answer, 1);

        while(smoothAnswer(answer) || shortenAnswer(answer, 0)){}

        std::cout << answer << std::endl;

        int sh = getClosest(Gesture, answer);
        if(sh != -1)
        {
            std::cout << Gesture[sh].shapeName << std::endl;
            loadShape(sh, Gesture);
        }

        mousePos.clear();
        answer = "-1";
    }

    if(isMouseDown)
    {
        Pos mp;
        SDL_GetMouseState(&mp.x, &mp.y);
//        std::cout << mp.x << " " << mp.y << std::endl;
        mousePos.push_back(mp);
    }
}

SDL_Rect button_rect;

int main(int arg, char* args[])
{

    button_rect.x = 100;
    button_rect.y = 100;
    button_rect.w = 201;
    button_rect.h = 181;

    if(!init()) std::cout << "Failed to initialize!";
    else
    if(!loadMedia()) std::cout << "Failed to load media!";
    else
    if(!loadShapeData(Gesture, gRenderer)) std::cout << "Failed to load shape data!";
    else
    {
        bool quit = false;
        SDL_Event e;
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT) {quit = true; break;}
                handleEvent(&e);
            }

            SDL_Delay(1000/fps);

            SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

            SDL_RenderCopy(gRenderer, button, NULL, &button_rect);

            SDL_RenderPresent(gRenderer);
//            SDL_RenderClear(gRenderer);
        }
    }
    close();
    return 0;
}
