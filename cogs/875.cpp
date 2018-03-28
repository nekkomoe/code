#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define FN "range"

const int N = 300;

int n, ans[N], pre[N][N], sub[N][N];

char mp[N][N];

int main() {
    freopen(FN ".in", "r", stdin);
    freopen(FN ".out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%s", mp[i] + 1);
    }

    for(int i = 1 ; i <= n ; i ++) {
        for(int j = 1 ; j <= n ; j ++) {
            pre[i][j] += pre[i][j - 1] + (mp[i][j] == '1');
            sub[i][j] += sub[i - 1][j] + (mp[i][j] == '1');
        }
    }

    for(int i = 1 ; i <= n ; i ++) {
        for(int j = 1 ; j <= n ; j ++) {
            for(int k = 2 ; k <= n ; k ++) {
                int x = i + k - 1, y = j + k - 1;
                if(!(1 <= x && x <= n && 1 <= y && y <= n) || mp[i][j] != '1') {
                    break;
                }
                if((pre[x][y] - pre[x][j - 1] == (y - j + 1)) && (sub[x][y] - sub[i - 1][y] == (x - i + 1))) {
                    ans[k] ++;
                } else {
                    break;
                }
            }
        }
    }
    for(int i = 2 ; i <= n ; i ++) {
        if(ans[i]) {
            printf("%d %d\n", i, ans[i]);
        }
    }
}
