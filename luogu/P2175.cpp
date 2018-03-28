// 动态规划 判定性dp 背包dp 二分图染色

%:pragma GCC optimize(2)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 2010;

int n, color[N], like[N][N], val[N][3], cnt;

bool f[N][N * 8];

vector<int> G[N];

void dfs(int u, int c, int dfn) {
    color[u] = c;
    ++ val[dfn][c];
    for(int i = 0 ; i < G[u].size() ; ++ i) {
        int v = G[u][i];
        if(!color[v]) {
            dfs(v, 3 - c, dfn);
        } else if(color[u] == color[v]) {
            puts("No solution");
            exit(0);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        while(scanf("%d", &x), x) {
            like[i][x] = 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j < i ; ++ j) {
            if(!(like[i][j] && like[j][i])) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!color[i]) {
            dfs(i, 1, ++ cnt);
        }
    }
    memset(f, 0, sizeof(f));
    #define dp(i, j) f[i][j + 4000]
    dp(0, 0) = 1;
    for(int i = 1 ; i <= cnt ; ++ i) {
        for(int j = -2000 ; j <= 2000 ; ++ j) {
            dp(i, j) |= dp(i - 1, j - val[i][1] + val[i][2]) | dp(i - 1, j - val[i][2] + val[i][1]);
        }
    }
    for(int i = 0 ; i <= 2000 ; ++ i) {
        if(dp(cnt, i)) {
            int x = (n + i) / 2, y = n - x;
            if(x > y) swap(x, y);
            printf("%d %d\n", x, y);
            return 0;
        } else if(dp(cnt, -i)) {
            int x = (n - i) / 2, y = n - x;
            if(x > y) swap(x, y);
            printf("%d %d\n", x, y);
            return 0;
        }
    }
    puts("No solution");
}
