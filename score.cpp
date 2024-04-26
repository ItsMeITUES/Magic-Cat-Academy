#include "headers/score.h"

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
