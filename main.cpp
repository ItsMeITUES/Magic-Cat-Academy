#include "shapes.h"
#include "recognizer.h"
#include "comparer.h"
#include "enemy.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const std::string SCREEN_TITLE = "Magic Cat Academy";

const int fps = 60;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL;
SDL_Texture* button = NULL;

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

    gTexture = IMG_LoadTexture(gRenderer, "images/backgrounds/Testing.png");
    if(gTexture == NULL) exit(0);

    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

    return success;
}

//void loadShape(int& shapeCodeName, shape shapeData[])
//{
//    SDL_Texture* shapeTexture = shapeData[shapeCodeName].texture;
//
//    if(shapeTexture == NULL)
//    {
//        std::cout << "Unable to load texture!";
//        return;
//    }
//
//    button = shapeTexture;
//}

void close(shape shapeData[], Enemy enemyData[])
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyTexture(button);
    button = NULL;

    destroyShapeTexture(shapeData);
    destroyEnemyTexture(enemyData);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Pos> mousePos;
std::string answer = "-1";

void handleEvent(SDL_Event *e, shape shapeData[], std::vector<EnemyClone> &enemies)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        isMouseDown = 1;
    }

    if(e->type == SDL_MOUSEBUTTONUP)
    {
        isMouseDown = 0;
        processMouseMovement(mousePos, answer);

        smoothenAnswer(answer);
        shortenAnswer(answer);

//        std::cout << answer << std::endl;

        int finalCode = getClosest(shapeData, answer);
        if(finalCode != -1)
        {
            std::cout << finalCode << " " << shapeData[finalCode].shapeName << std::endl;
            damageEnemy(enemies, finalCode);
//            loadShape(sh, shapeData);
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
//    button_rect.x = 100;
//    button_rect.y = 100;
//    button_rect.w = 201;
//    button_rect.h = 181;

    Enemy enemyData[5];
    std::vector<EnemyClone> enemies;

    shape shapeData[10];

    if(!init()) {std::cout << "Failed to initialize!"; return 0;}
    if(!loadMedia()) {std::cout << "Failed to load media!"; return 0;}
    if(!loadShapeData(shapeData, gRenderer)) {std::cout << "Failed to load shape data!";return 0;}
    if(!loadEnemyData(enemyData, gRenderer)) {std::cout << "Failed to load shape data!";return 0;}

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        SDL_RenderClear(gRenderer);

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) {quit = true; break;}
            handleEvent(&e, shapeData, enemies);
        }

        SDL_Delay(1000/fps);

        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

//            SDL_RenderCopy(gRenderer, button, NULL, &button_rect);
        enemySpawner(enemyData, enemies, SCREEN_WIDTH, SCREEN_HEIGHT);

        handleBasicEnemy(enemies);

        drawEnemy(shapeData, enemyData, enemies, gRenderer);

        SDL_RenderPresent(gRenderer);
    }
    close(shapeData, enemyData);
    return 0;
}
