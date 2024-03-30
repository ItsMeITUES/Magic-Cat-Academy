#pragma once
#include "shapes.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>

const int basicEnemyDelay = 100;
const int scaleDown = 5;

enum enemyType
{
    basicEnemy = 1,
    eliteEnemy,
    bossEnemy
};

struct Enemy
{
    int id;
    std::string name, hpBar = "*";
    int spawnCD, health, speed;
    SDL_Texture* texture = NULL;
    SDL_Rect rect;
};

struct EnemyClone
{
    int id;
    std::string name, hpBar = " ";
    int health, speed;
    SDL_Rect rect;
    double moveX, moveY;
    double posX, posY;
};

bool loadEnemyData(Enemy enemyData[], SDL_Renderer* gRenderer);
EnemyClone spawnEnemy(Enemy enemyData[], enemyType type, int spawnX, int spawnY, int desX, int desY);
void handleBasicEnemy(std::vector<EnemyClone>& enemies);

void enemySpawner(Enemy enemyData[], std::vector<EnemyClone>& enemies, int ScreenW, int ScreenH);
void drawEnemy(shape shapeData[], Enemy enemyData[], std::vector<EnemyClone>& enemies, SDL_Renderer* gRenderer);

void damageEnemy(std::vector<EnemyClone>& enemies, int code);

void destroyEnemyTexture(Enemy enemyData[]);
