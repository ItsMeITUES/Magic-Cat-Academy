#ifndef __SCORE
#define __SCORE

#include "animation.h"
#include "enemy.h"

#include <string>

void renderScore(int& totalScore, std::string& scoreString, LTexture& scoreText, SDL_Renderer* gRenderer);

void changeEnemyData(int& totalScore, Enemy enemyData[]);

void resetEnemyData(Enemy enemyData[], double spd1, double spd2);

#endif // __SCORE
