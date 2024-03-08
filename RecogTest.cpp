#include <iostream>
#include <vector>

using namespace std;

//vectors for mouse positions
struct Pos
{
    int x, y;
};

vector<Pos> mouse;

int main()
{
//    In main SDL I have to record mouse movement as soon as mouse_down
//    and stop when mouse_up
//    Ideally I will record mouse positions each x second(s)
//    and store them in a vector<> mouse_position

//    In this test program I will read mouse positions from a pre-recorded file

    freopen("mtest.inp", "r", stdin);

    int mouse_pos_x = 0, mouse_pos_y = 0;
    while(cin >> mouse_pos_x >> mouse_pos_y)
    {
        Pos mp;
        mp.x = mouse_pos_x;
        mp.y = mouse_pos_y;
        mouse.push_back(mp);
    }

    for(auto u : mouse) cout << u.x << " " << u.y << endl;
}
