// 二维前缀和 图的性质 连通块

/*
  对于不包含环的图,连通块数目=点数-边数（这是什么鬼。。。）
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 2010;

char mp[N][N];

int n, m, q, a[N][N], c[N][N], b[N][N];

#define plus(arr, val, i, j) arr[i][j] = arr[i][j - 1] + arr[i - 1][j] - arr[i - 1][j - 1] + (val)

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", mp[i] + 1);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            plus(a, mp[i][j] == '1', i, j);
            plus(b, mp[i][j] == '1' && mp[i][j - 1] == '1', i, j);
            plus(c, mp[i][j] == '1' && mp[i - 1][j] == '1', j, i);
        }
    }

    for(int i = 1, x, y, xx, yy ; i <= q ; ++ i) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        printf("%d\n",
               (a[xx][yy] - a[x - 1][yy] - a[xx][y - 1] + a[x - 1][y - 1]) -
               (b[xx][yy] - b[xx][y] - b[x - 1][yy] + b[x - 1][y]) -
               (c[yy][xx] - c[yy][x] - c[y - 1][xx] + c[y - 1][x]));
    }
}
