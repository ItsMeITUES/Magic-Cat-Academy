#include "headers/recognizer.h"

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
    else ansCode = "-1";
//    std::cout << input_len << std::endl;

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
bool smoothenAnswer(std::string& answer)
{
    if(answer == "-1") return 0;

    bool success = 0;
    int p = answer.size();
    if(p < 3) return 0;

    for(int i = 1; i < p - 1; i++)
    {
        if(answer[i] % 2) continue;

        if(std::abs((answer[i] - answer[i - 1] + 1) % sliceNum - 1) == 1
        && std::abs((answer[i] - answer[i + 1] + 1) % sliceNum - 1) == 1
        && answer[i - 1] == answer[i + 1])
        {
            answer[i] = answer[i - 1];
            success = 1;
        }
    }
    return success;
}

//2222222 1111111555555 33333333
bool shortenAnswer(std::string& answer)
{
    if(answer == "-1") return 0;

    bool success = 0;
    int p = answer.size();

    std::string shorten = "";

    char now = answer[0];
    int codeCount = 1;

    for(int i = 1; i < p; i++)
    {
        if(answer[i] == now)
        {
            codeCount++;
            success = 1;
            continue;
        }
        if(codeCount >= minAllowedCount)
            shorten = shorten + now;
        now = answer[i];
        codeCount = 1;
    }
    if(codeCount >= minAllowedCount)
        shorten = shorten + now;
    answer = shorten;
    return success;
}
