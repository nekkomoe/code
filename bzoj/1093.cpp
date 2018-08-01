#include "bits/stdc++.h"
using namespace std;
const int N = 2000000 + 10;
int n, m, p;
int head[N], rest[N], to[N], tot;
void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
int dfn[N], low[N], clk, instack[N];
stack<int> sta;
int id[N], cnt, f[N], mx[N], val[N], deg[N], from[N];
void dfs(int u) {
    dfn[u] = low[u] = ++ clk;
    sta.push(u), instack[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
        else if(instack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        int v;
        ++ cnt;
        do {
            v = sta.top(); sta.pop(); instack[v] = 0;
            id[v] = cnt;
            ++ val[cnt];
        } while(u != v);
    }
}
vector<int> G[N];
queue<int> q;
int main() {
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 1, u, v ; i <= m ; ++ i) scanf("%d%d", &u, &v), add(u, v);
    for(int i = 1 ; i <= n ; ++ i) if(!dfn[i]) dfs(i);
    for(int u = 1 ; u <= n ; ++ u) {
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(id[u] != id[v]) {
                G[id[u]].push_back(id[v]);
                ++ deg[id[v]];
            }
        }
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(deg[i] == 0) {
            q.push(i);
            f[i] = 1;
            mx[i] = val[i];
        }
    }
    int ans = 0, sum = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < G[u].size() ; ++ i) {
            int v = G[u][i];
            if(!-- deg[v]) q.push(v);
            if(from[v] == u) continue;
            if(mx[u] + val[v] > mx[v]) {
                mx[v] = mx[u] + val[v];
                f[v] = f[u];
            } else if(mx[u] + val[v] == mx[v]) {
                f[v] = (f[v] + f[u]) % p;
            }
            from[v] = u;
        }
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(ans < mx[i]) {
            ans = mx[i];
            sum = f[i];
        } else if(ans == mx[i]) {
            sum = (sum + f[i]) % p;
        }
    }
    printf("%d\n%d\n", ans, sum);
}
