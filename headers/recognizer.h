#ifndef __RECOG
#define __RECOG

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Pos
{
    int x, y;
};

const short sliceNum = 8;
const short smoothConst = 2;
const int minAllowedCount = 2;
// tangent constants of directional slices
const double sliceBorderTan[] =
{
    -0.4142135624,
    0.4142135624,
    2.4142135624,
    -2.4142135624,
    -0.4142135624
};
void addCalculated(std::string& directionCode, double& dir, double& difX, double& difY);
void processMouseMovement(std::vector<Pos>& mouse, std::string& ansCode);
bool smoothenAnswer(std::string& answer);
bool shortenAnswer(std::string& answer);

#endif // __RECOG
