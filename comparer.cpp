#include "comparer.h"
#include "shapes.h"

int checkMLD(std::string x, std::string y)
{
    int n = x.size();
    int m = y.size();
    x = " " + x;
    y = " " + y;

    if(n < m) return 10;

    int dist[n + 5][m + 5];
    for(int i = 0; i <= n; i++) dist[i][0] = i;
    for(int j = 0; j <= m; j++) dist[0][j] = j;

    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
    {
        if(x[i] == y[j]) dist[i][j] = dist[i - 1][j - 1];
        else dist[i][j] = 1 + std::min(std::min(dist[i][j - 1], dist[i - 1][j]), dist[i - 1][j - 1]);
    }

    return dist[n][m];
}

int getClosest(shapes Gesture[], std::string& ans)
{
    if(ans == "-1") return -1;
    int Total = Gesture[0].codeCount;

    int resultCode = -1, resultDiff = inf;

    for(int i = 1; i <= Total; i++)
    {
        int diff = inf;
        for(int j = 1; j <= Gesture[i].codeCount; j++)
            diff = std::min(diff, checkMLD(ans, Gesture[i].codes[j]));
        if(diff < resultDiff)
        {
            resultCode = i;
            resultDiff = diff;
        }
    }

    if(resultDiff > maxAllowedDiff) return -1;

    return resultCode;
}
