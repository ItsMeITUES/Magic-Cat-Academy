#include "recognizer.h"

void addCalculated(std::string& directionCode, double& dir, bool dx0, bool dy0)
{
    short dirCode = 0;
    if(dir > sliceBorderTan[0] && dir <= sliceBorderTan[1])
        dirCode = (dx0? 0 : 4);
    else if(dir > sliceBorderTan[1] && dir <= sliceBorderTan[2])
        dirCode = (dx0? 1 : 5);
    else if(dir > sliceBorderTan[2] || dir <= sliceBorderTan[3])
        dirCode = (dy0? 2 : 6);
    else if(dir > sliceBorderTan[3] && dir <= sliceBorderTan[4])
        dirCode = (dy0? 3 : 7);

    directionCode = directionCode + char(dirCode + '0');
}

void processMouseMovement(std::vector<Pos>& mouse, std::string& ansCode)
{
    int input_len = mouse.size();

    if(input_len > 1) ansCode = "";

    for(int i = 0; i < input_len - 1; i++)
    {
        int currentX = mouse[i].x;
        int currentY = - mouse[i].y;

        int nextX = mouse[i + 1].x;
        int nextY = - mouse[i + 1].y;

        double difX = nextX - currentX;
        double difY = nextY - currentY;

        double rawDir = difY / difX;

        addCalculated(ansCode, rawDir, (difX > 0), (difY > 0));
    }
    return;
}

//
bool smoothAnswer(std::string& answer)
{
    bool success = 0;
    int p = answer.size();
    if(p < 3) return 0;

    std::string smoothed = "";

    char x = answer[0];
    smoothed = smoothed + x;

    for(int i = 1; i < p - 1; i++)
    {
        if(std::abs((answer[i] - answer[i - 1] + 1) % sliceNum - 1) != 1
        || std::abs((answer[i] - answer[i + 1] + 1) % sliceNum - 1) != 1
        || answer[i - 1] != answer[i + 1])
            smoothed = smoothed + answer[i];
        else success = 1;
    }
    x = answer[p - 1];
    smoothed = smoothed + x;

    answer = smoothed;
    return success;
}

//2222222 1111111555555 33333333
bool shortenAnswer(std::string& answer)
{
    bool success = 0;
    int p = answer.size();
    std::string shorten = "";

    char now = answer[0];

    for(int i = 1; i < p; i++)
    {
        if(answer[i] == now)
        {
            success = 1;
            continue;
        }
        shorten = shorten + now;
        now = answer[i];
    }
    shorten = shorten + now;
    answer = shorten;
    return success;
}

// 76767676 12121212
void smootherAnswer(std::string& answer)
{
    int p = answer.size();

    std::string smoothed = "";

    int index = 0;
    char x = '-', y = '-';
    bool isSet = 0;
    bool odd = 0;

    while(index < p && (answer[index] - '0') % 2 == 0)
    {
        smoothed = smoothed + answer[index];
        index++;
    }
//    std::cout << answer << std::endl;
    while(index < p)
    {
        if((answer[index] - '0') % 2 == 1)
        {
            if(isSet)
            {
                if(answer[index] == x)
                {
                    odd = 0;
                    index++;
                    continue;
                }
                if(x != '-')
                {
                    smoothed = smoothed + x;
                    if(y != x && y != '-') smoothed += y;
                }
            }
            else isSet = 1;

            x = answer[index];
            y = answer[index];
        }
        else
        {
            if(isSet)
            {
                if(std::abs((answer[index] - x + 1) % sliceNum - 1) <= 1)
                {
                    if((y == x || answer[index] == y) && !odd)
                    {
                        y = answer[index];
                        odd = 1;
                    }
                    else
                    {
                        smoothed = smoothed + x;
                        smoothed = smoothed + y;
                        isSet = 0;
                        odd = 0;
                    }
                }
                else
                {
                    smoothed = smoothed + x;
                    isSet = 0;
                    odd = 0;
                }
            }
            else smoothed = smoothed + answer[index];
        }
        index++;
    }
    if(isSet) smoothed += x;

//    std::cout << answer << std::endl;
    answer = smoothed;
    return;
}


