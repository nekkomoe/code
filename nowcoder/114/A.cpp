#include "bits/stdc++.h"
using namespace std;
 
int a[1010][1010], n, m;
 
int mv[4][2] = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0}
};
 
bool benxt(int x, int y, int i) {
    int nx = x + mv[i][0], ny = y + mv[i][1];
    return 1 <= nx && nx <= n && 1 <= ny && ny <= n && !a[nx][ny];
}
 
int main() {
    cin >> n >> m;
    int x = 1, y = 1, i = 3;
    a[x][y] = 1;
    while(m --) { while(!benxt(x, y, i)) (++ i) %= 4; a[x += mv[i][0]][y += mv[i][1]] = 1; }
    cout << x << ' ' << y << endl;
}
