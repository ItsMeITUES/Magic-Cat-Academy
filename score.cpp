#include "headers/score.h"

#include <fstream>

void changeEnemyData(int& totalScore, Enemy enemyData[])
{
    if(totalScore >= 30)
    {
        enemyData[1].health = 2;
        enemyData[2].health = 6;
    }
    enemyData[1].speed *= (1.3 + 100) / 100;
    enemyData[2].speed *= (1.3 + 100) / 100;
}

void resetEnemyData(Enemy enemyData[], double spd1, double spd2)
{
    enemyData[1].health = 1;
    enemyData[2].health = 5;
    enemyData[1].speed = spd1;
    enemyData[2].speed = spd2;
}

void renderScore(int& totalScore, std::string& scoreString, LTexture& scoreText, SDL_Renderer* gRenderer)
{
//                    totalScore = 999;
    scoreString = "";
    SDL_Color textColor = { 255, 255, 255 };

    if(totalScore == 0) scoreString = "Score: 0";
    else
    {
        int x = totalScore;

//        std::cout << totalScore << std::endl;

        while(x > 0)
        {
            scoreString = char(x % 10 + '0') + scoreString;
            x /= 10;
        }
        scoreString = "Score: " + scoreString;
//        std::cout << scoreString << std::endl;
    }

    if(!scoreText.loadFromRenderedText(scoreString, textColor, gRenderer) )
    {
       std::cout << "Failed to render text texture!" << std::endl;
    }
}
