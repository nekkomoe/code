#include <bits/stdc++.h>
using namespace std;
const int N = 510;
vector<int> g[N];
int mat[N], vis[N], n, m, T;

inline void read(int &x) {
    char c = x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int dfs(int u) {
    vis[u] = T;
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(vis[v] == T) continue;
        vis[v] = T;
        if(!mat[v] || dfs(mat[v])) {
            mat[v] = u, mat[u] = v;
            return 1;
        }
    }
    return 0;
}

int main() {
    read(n), read(m);
    for(int i = 1, u, v ; i <= m ; ++ i)
        read(u), read(v), g[u].push_back(v), g[v].push_back(u);
    int res = 0;
    for(int i = 1 ; i <= n ; ++ i)
        if(!mat[i])
            ++ T, res += dfs(i);
    printf("%d", n - res);
}
