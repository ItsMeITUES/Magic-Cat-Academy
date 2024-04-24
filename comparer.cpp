#include "comparer.h"

int checkMLD(std::string x, std::string y)
{
    int n = x.size();
    int m = y.size();
    x = " " + x;
    y = " " + y;

    int dist[n + 1][m + 1];
    for(int i = 0; i <= n; i++) dist[i][0] = i;
    for(int j = 0; j <= m; j++) dist[0][j] = j;

    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
    {
        if(x[i] == y[j]) dist[i][j] = dist[i - 1][j - 1];
        else
            dist[i][j] = 1 + std::min(std::min(dist[i][j - 1], dist[i - 1][j]), dist[i - 1][j - 1]);
    }

    return dist[n][m];
}

int getClosest(shape shapeData[], std::string& ans)
{
    if(ans == "-1") return -1;
    int Total = shapeData[0].codeCount;

    int resultCode = -1, resultDiff = inf;

//    std::cout << Total << std::endl;

    for(int i = 1; i <= Total; i++)
    {
        int diff = inf;
        for(int j = 1; j <= shapeData[i].codeCount; j++)
            diff = std::min(diff, checkMLD(ans, shapeData[i].codes[j]));

//        std::cout << shapeData[i].shapeName << std::endl;
//        std::cout << diff << std::endl;

        if(diff > shapeData[i].maxAllowedDiff) diff = inf;
        else
        if(diff < resultDiff)
        {
            resultCode = i;
            resultDiff = diff;
        }
    }

//    std::cout << resultDiff << std::endl;
//    std::cout << checkMLD("107", "17") << std::endl;

    if(resultDiff == inf) resultCode = -1;

    return resultCode;
}
