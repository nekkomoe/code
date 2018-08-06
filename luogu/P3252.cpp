//dfs+树上前缀和

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 100010;

int n, S, val[N], fa[N], ans;

vector<int> G[N];

void dfs(int u) {
    val[u] += val[fa[u]];
    if(val[u] >= S) {
        int v = u;
        while(v) {
            if(val[u] - val[v] == S) {
                ans ++;
            }
            if(val[u] - val[v] >= S) {
                goto nxt;
            }
            v = fa[v];
        }
        ans += val[u] - val[v] == S;
    }
 nxt:
    for(int i = 0 ; i < G[u].size() ; i ++) {
        int v = G[u][i];
        dfs(v);
    }
}

int main() {
    scanf("%d%d", &n, &S);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &val[i]);
    }
    for(int i = 1, x, y ; i < n ; i ++) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        fa[y] = x;
    }
    dfs(1);
    printf("%d\n", ans);
}
