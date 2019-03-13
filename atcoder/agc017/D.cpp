#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

vector<int> g[N];

int n;

int dfs(int u, int fa) {
    int res = 0;
    for(int v: g[u]) {
        if(v != fa) {
            res ^= dfs(v, u) + 1;
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    puts(dfs(1, 0) ? "Alice" : "Bob");
}
