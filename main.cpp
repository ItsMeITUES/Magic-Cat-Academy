#include "headers/shapes.h"
#include "headers/recognizer.h"
#include "headers/comparer.h"
#include "headers/enemy.h"
#include "headers/animation.h"
#include "headers/player.h"
#include "headers/button.h"
#include "headers/score.h"
#include "headers/music.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const std::string SCREEN_TITLE = "Magic Cat Academy";

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;
const int fps = 60;

SFX menuTheme;
SFX playTheme;
SFX overTheme;

int gameState = 0;
// 0 - start menu
// 1 - playing
// 2 - game over

//score system
int totalScore = 0;
LTexture scoreText;
std::string scoreString = "-1";

//backgrounds
SDL_Texture* gameStart = NULL;
SDL_Texture* gamePlay = NULL;
SDL_Texture* gameOver = NULL;

//buttons
button playButton;
button restartButton;
button homeButton;

double player_scale = 0.5;
double play_button_scale = 0.5;
double restart_button_scale = 0.5;
double home_button_scale = 0.5;

bool isMouseDown = 0;

bool init()
{
    bool success = 1;

    if(( SDL_INIT_VIDEO | SDL_INIT_AUDIO )< 0)
    {
        std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError();
        success = 0;
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = 0;
    }

    gWindow = SDL_CreateWindow("Magic Cat Academy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        std::cout << "Cannot create Window! SDL Error: " << SDL_GetError();
        success = 0;
    }
    else
    {
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = 1;

    gameStart = IMG_LoadTexture(gRenderer, "images/backgrounds/gameStart.png");

    if(gameStart == NULL) std::cout << "SDL_IMG Error: " << IMG_GetError() << std::endl;

    gamePlay = IMG_LoadTexture(gRenderer, "images/backgrounds/gamePlay.png");

    if(gamePlay == NULL) std::cout << "SDL_IMG Error: " << IMG_GetError() << std::endl;

    gameOver = IMG_LoadTexture(gRenderer, "images/backgrounds/gameOver.png");

    if(gameOver == NULL) std::cout << "SDL_IMG Error: " << IMG_GetError() << std::endl;

    playButton.path = "images/button/play_button.png";
    playButton.type = "circle";
    playButton.scaler = play_button_scale;
    playButton.setRect(0, 0, 200, 200);
    playButton.setPos(350, 270);
    playButton.texture.loadFromFile(playButton.path, gRenderer);

    restartButton.path = "images/button/restart_button.png";
    restartButton.type = "circle";
    restartButton.scaler = restart_button_scale;
    restartButton.setRect(0, 0, 200, 200);
    restartButton.setPos(525, 300);
    restartButton.texture.loadFromFile(restartButton.path, gRenderer);

    homeButton.path = "images/button/home_button.png";
    homeButton.type = "circle";
    homeButton.scaler = home_button_scale;
    homeButton.setRect(0, 0, 200, 200);
    homeButton.setPos(670, 300);
    homeButton.texture.loadFromFile(homeButton.path, gRenderer);

    scoreText.loadFont("fonts/00803_AbrazoScriptSSiBold.ttf", 50);

    menuTheme.loadMusic("music/Ace in the Hole - Honkai： Star Rail 2.0 OST.wav");
    playTheme.loadMusic("music/The Player on The Other Side · Penacony Battle Theme - Honkai： Star Rail 2.0 OST.wav");
    overTheme.loadMusic("music/The Big Sleep - Honkai： Star Rail 2.0 OST.wav");

    Mix_VolumeMusic(50);

//    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

//    std::cout << playButton.rect.w << playButton.rect.h << std::endl;

//    playButton.texture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gRenderer, &playButton.rect, play_button_scale);

    return success;
}

void close(shape shapeData[], Enemy enemyData[], Player playerData[])
{
    SDL_DestroyTexture(gameStart);
    gameStart = NULL;

    SDL_DestroyTexture(gamePlay);
    gamePlay = NULL;

    SDL_DestroyTexture(gameOver);
    gameOver = NULL;

    destroyShapeTexture(shapeData);
    destroyEnemyTexture(enemyData);
//    destroyEnemyTexture(enemyData);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

std::vector<Pos> mousePos;
std::string answer = "-1";

void handleEvent(SDL_Event *e, shape shapeData[], std::vector<EnemyClone>& enemies, Enemy enemyData[], Player playerData[])
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        isMouseDown = 1;
    }

    if(e->type == SDL_MOUSEBUTTONUP)
    {
        isMouseDown = 0;

        switch(gameState)
        {
            case 0:
            {
                Pos mp;
                SDL_GetMouseState(&mp.x, &mp.y);
                if(isMouseOn(playButton, mp.x, mp.y)) playButton.mouseUpHere = 1;

                if(playButton.mouseDownHere && playButton.mouseUpHere)
                {
                    scoreText.free();
                    totalScore = 0;
                    renderScore(totalScore, scoreString, scoreText, gRenderer);
                    resetEnemyData(enemyData, 1.2, 1);
                    gameState = 1;

                    menuTheme.stopMusic();
                }

                playButton.mouseDownHere = 0;
                playButton.mouseUpHere = 0;
            }break;

            case 1:
            {
                processMouseMovement(mousePos, answer);
                smoothenAnswer(answer);
                shortenAnswer(answer);

        //        std::cout << answer << std::endl;

                int finalCode = getClosest(shapeData, answer);
                if(finalCode != -1)
                {
                    int x = totalScore;
        //            std::cout << finalCode << " " << shapeData[finalCode].shapeName << std::endl;
                    damageEnemy(enemies, enemyData, finalCode, totalScore);
//                    std::cout << playerData[1].casted.getChunk() << std::endl;
                    playerData[1].casted.playChunk();
                    if(totalScore > x)
                    {
                        renderScore(totalScore, scoreString, scoreText, gRenderer);
                        changeEnemyData(totalScore, enemyData);
                    }
        //            loadShape(sh, shapeData);
                }

                mousePos.clear();
                answer = "-1";
            }break;

            case 2:
            {
                Pos mp;
                SDL_GetMouseState(&mp.x, &mp.y);
                if(isMouseOn(restartButton, mp.x, mp.y)) restartButton.mouseUpHere = 1;

                if(restartButton.mouseDownHere && restartButton.mouseUpHere)
                {
                    scoreText.free();
                    totalScore = 0;
                    renderScore(totalScore, scoreString, scoreText, gRenderer);
                    resetEnemyData(enemyData, 1.2, 1);
                    gameState = 1;

                    overTheme.stopMusic();
                }

                restartButton.mouseDownHere = 0;
                restartButton.mouseUpHere = 0;

                if(isMouseOn(homeButton, mp.x, mp.y)) homeButton.mouseUpHere = 1;

                if(homeButton.mouseDownHere && homeButton.mouseUpHere)
                {
                    gameState = 0;

                    overTheme.stopMusic();
                }

                homeButton.mouseDownHere = 0;
                homeButton.mouseUpHere = 0;
            }break;

            default:{}
        }


    }

    if(isMouseDown)
    {
        switch(gameState)
        {
            case 0:
            {
                Pos mp;
                SDL_GetMouseState(&mp.x, &mp.y);
                if(isMouseOn(playButton, mp.x, mp.y)) playButton.mouseDownHere = 1;
            } break;

            case 1:
            {
                Pos mp;
                SDL_GetMouseState(&mp.x, &mp.y);
        //        std::cout << mp.x << " " << mp.y << std::endl;
                mousePos.push_back(mp);
            } break;

            case 2:
            {
                Pos mp;
                SDL_GetMouseState(&mp.x, &mp.y);
                if(isMouseOn(restartButton, mp.x, mp.y)) restartButton.mouseDownHere = 1;
                if(isMouseOn(homeButton, mp.x, mp.y)) homeButton.mouseDownHere = 1;
            } break;

            default:{}
        }
    }
}

int main(int arg, char* args[])
{
    gameState = 0;

    Enemy enemyData[5];
    std::vector<EnemyClone> enemies;

    shape shapeData[10];

    Player playerData[10];
    Cat cat;

    if(!init()) {std::cout << "Failed to initialize!"; return 0;}
    if(!loadMedia()) {std::cout << "Failed to load media!"; return 0;}
    if(!loadShapeData(shapeData, gRenderer)) {std::cout << "Failed to load shape data!";return 0;}
    if(!loadEnemyData(enemyData, gRenderer)) {std::cout << "Failed to load enemy data!";return 0;}
    if(!loadPlayerData(playerData, gRenderer)) {std::cout << "Failed to load player data!";return 0;}

    selectPlayer(1, cat, playerData, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        int prevTime = SDL_GetTicks();

        SDL_RenderClear(gRenderer);

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) {quit = true; break;}
            handleEvent(&e, shapeData, enemies, enemyData, playerData);
        }

//        std::cout << gameState << std::endl;

//        playButton.texture.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gRenderer, &playButton.rect, playButton.scaler);

        scoreText.renderText(gRenderer, ( SCREEN_WIDTH - scoreText.getWidth() ) / 2, ( SCREEN_HEIGHT - scoreText.getHeight() ) / 2);

        switch(gameState)
        {
            case 0:
            {
                menuTheme.playMusic();

                SDL_RenderCopy(gRenderer, gameStart, NULL, NULL);
                playButton.texture.render(playButton.posX, playButton.posY, gRenderer, &playButton.rect, playButton.scaler);
            }break;

            case 1:
            {
                playTheme.playMusic();

                SDL_RenderCopy(gRenderer, gamePlay, NULL, NULL);

                enemySpawner(enemyData, enemies, SCREEN_WIDTH, SCREEN_HEIGHT);

                handleBasicEnemy(enemies, gameState, playTheme);

                if(isMouseDown) playAnimation(playerData[cat.id].cast, gRenderer, cat.posX, cat.posY, player_scale);
                else playAnimation(playerData[cat.id].idle, gRenderer, cat.posX, cat.posY, player_scale);

                drawEnemy(shapeData, enemyData, enemies, gRenderer);

                scoreText.renderText(gRenderer, 0, 0);
            }break;

            case 2:
            {
                overTheme.playMusic();

                SDL_RenderCopy(gRenderer, gameOver, NULL, NULL);

                restartButton.texture.render(restartButton.posX, restartButton.posY, gRenderer, &restartButton.rect, restartButton.scaler);

                homeButton.texture.render(homeButton.posX, homeButton.posY, gRenderer, &homeButton.rect, homeButton.scaler);

                scoreText.renderText(gRenderer, 510, 170);
            }break;

            default:{}
        }

        SDL_RenderPresent(gRenderer);

        double processTime = SDL_GetTicks() - prevTime;
        SDL_Delay(1000/fps - 0.001 * processTime);
    }

    close(shapeData, enemyData, playerData);
    return 0;
}
