//二分图染色 模拟 枚举
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n;

long long cnt[2], sz[N], ans;

vector<int> G[N], lef;

void dfs(int u, int f = 0, int color = 0) {
    cnt[color] ++;
    if(!color) {
        lef.push_back(u);
    }
    for(int i = 0 ; i < G[u].size() ; i ++) {
        int v = G[u][i];
        if(v != f) {
            sz[u] ++;
            sz[v] = 1;
            dfs(v, u, color ^ 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; i ++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);
    for(int i = 0 ; i < lef.size() ; i ++) {
        int u = lef[i];
        ans += cnt[1] - sz[u];
    }
    cout << ans << endl;
}
