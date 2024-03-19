#include "enemy.h"
#include <fstream>

bool loadEnemyData(Enemy enemyData[], SDL_Renderer* gRenderer)
{
    srand(time(NULL));

    bool success = 1;

    std::ifstream inFile;
    inFile.open("data/enemy.txt");

    if(!inFile)
     {
         std::cout << "Failed to load enemy data!";
         success = 0;
         return success;
     }

    int Total;
    inFile >> Total;

    enemyData[0].id = Total;

//    std::cout << enemyData[0].codeCount << std::endl;

    for(int i = 1; i <= Total; i++)
    {
        inFile >> enemyData[i].id >> enemyData[i].name
        >> enemyData[i].spawnCD >> enemyData[i].health >> enemyData[i].speed;

        std::string path;
        inFile >> path;

        enemyData[i].texture = IMG_LoadTexture(gRenderer, path.c_str());
        if(enemyData[i].texture == NULL)
        {
            std::cout << "Failed to load enemy texture! SDL_image error: " << IMG_GetError();
            success = 0;
            return success;
        }

        inFile >> enemyData[i].rect.w >> enemyData[i].rect.h;
    }

    inFile.close();

    return success;
}

EnemyClone spawnEnemy(Enemy enemyData[], enemyType type, int spawnX, int spawnY, int desX, int desY)
{
    EnemyClone now;

    now.id = type;
    now.name = enemyData[type].name;
    now.hpBar = enemyData[type].hpBar;

    now.health = enemyData[type].health;
    now.speed = enemyData[type].speed;
    now.rect = enemyData[type].rect;

    now.rect.w /= scaleDown;
    now.rect.h /= scaleDown;

    for(int i = 1; i <= now.health; i++)
    {
        now.hpBar += char(rand() % 4 + '1');
    }

    now.rect.x = spawnX;
    now.rect.y = spawnY;

    now.posX = spawnX;
    now.posY = spawnY;

    int diffX = desX - spawnX;
    int diffY = desY - spawnY;

    double distance = sqrt(diffX * diffX + diffY * diffY);

    double spd = now.speed;

    now.moveX = (spd / distance) * diffX;
    now.moveY = (spd / distance) * diffY;

//    std::cout << now.speed << std::endl;
//    std::cout << diffX << " " << diffY << std::endl;
//    std::cout << now.moveX << " " << now.moveY << std::endl;

    return now;
}

void handleBasicEnemy(std::vector<EnemyClone>& enemies)
{
    int totalEnemy = enemies.size();
    for(int i = 0; i < totalEnemy; i++)
    {
        enemies[i].posX += enemies[i].moveX;
        enemies[i].posY += enemies[i].moveY;
        enemies[i].rect.x = enemies[i].posX;
        enemies[i].rect.y = enemies[i].posY;
//        std::cout << i << enemies[i].moveX << " " << enemies[i].moveY << std::endl;
    }
}

void enemySpawner(Enemy enemyData[], std::vector<EnemyClone>& enemies, int ScreenW, int ScreenH)
{
    int timeNow = SDL_GetTicks();
    int Total = enemyData[0].id;

    for(int i = 1; i <= Total; i++)
    {
        if(timeNow - enemyData[i].spawnCD > basicEnemyDelay)
        {
            int spawnX = 0, spawnY = 0;

            if(rand() % 2)
            {
                spawnX = -50  + (rand() % 2) * (ScreenW + 50);
                spawnY = rand() % (ScreenH - ScreenH / 10) + ScreenH / 5;
            }
            else
            {
                spawnX = rand() % (ScreenW - ScreenW / 10) + ScreenW / 5;
                spawnY = -50  + (rand() % 2) * (ScreenH + 50);
            }

            EnemyClone newEnemy = spawnEnemy(enemyData, basicEnemy, spawnX, spawnY, ScreenW / 2, ScreenH / 2);
            enemies.push_back(newEnemy);

            enemyData[i].spawnCD = timeNow;
        }
    }
}

void damageEnemy(std::vector<EnemyClone> &enemies, int code)
{
    int totalEnemy = enemies.size();
    std::vector<EnemyClone> updatedEnemies;

    updatedEnemies.clear();

    for(int i = 0; i < totalEnemy; i++)
    {
        std::string calculatedHP = "*";

//        std::cout << enemies[i].hpBar << " ";

        for(int j = 1; j <= enemies[i].health; j++)
        {
            if(enemies[i].hpBar[j] - '0' != code)
                calculatedHP += enemies[i].hpBar[j];
        }
        enemies[i].hpBar = calculatedHP;

//        std::cout << "aaa" << calculatedHP << "aaa" << "a" << "aaa" << std::endl;
//        std::cout << (calculatedHP == "*") << std::endl;
        if(calculatedHP != "*" ) updatedEnemies.push_back(enemies[i]);
//        else std::cout << "aa" << updatedEnemies.size() << std::endl;
//        std::cout << i << enemies[i].moveX << " " << enemies[i].moveY << std::endl;
    }
//    std::cout << std::endl;

//    std::cout << (enemies.size()) - (updatedEnemies.size()) << std::endl;
//    enemies.clear();
    enemies = updatedEnemies;
}

void drawEnemy(shape shapeData[], Enemy enemyData[], std::vector<EnemyClone>& enemies, SDL_Renderer* gRenderer)
{
    int totalEnemy = enemies.size();
//    std::cout << totalEnemy << std::endl;
    for(int i = 0; i < totalEnemy; i++)
    {
        SDL_RendererFlip flipType = SDL_FLIP_NONE;
        if(enemies[i].moveX >= 0) flipType = SDL_FLIP_HORIZONTAL;

        SDL_RenderCopyEx(gRenderer, enemyData[enemies[i].id].texture, NULL, &enemies[i].rect, 0, NULL, flipType);

        SDL_Rect hpRect;

        double scaler = enemies[i].rect.w;
        scaler = (scaler / shapeData[1].rect.w) / 2;

        hpRect.w = scaler * shapeData[1].rect.w;
        hpRect.h = scaler * shapeData[1].rect.h;

        hpRect.x = enemies[i].posX + enemies[i].rect.w / 2 - hpRect.w / 2;
        hpRect.y = enemies[i].posY - hpRect.h;

        for(int j = 1; j <= enemies[i].health; j++)
        {
            int healthCode = enemies[i].hpBar[j] - '0';
            SDL_RenderCopy(gRenderer, shapeData[healthCode].texture, NULL, &hpRect);
        }
    }
}

void destroyEnemyTexture(Enemy enemyData[])
{
    int Total = enemyData[0].id;
    for(int i = 1; i <= Total; i++)
    {
        SDL_DestroyTexture(enemyData[i].texture);
        enemyData[i].texture = NULL;
    }
}
