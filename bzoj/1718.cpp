#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int head[N], rest[N], to[N], tot, tag[N];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int dfn[N], low[N], clk, id[N], cnt, deg[N];

stack<int> s;

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++ clk;
    s.push(u);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(tag[i] != fa) {
            if(!dfn[v]) {
                dfs(v, tag[i]), low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if(low[u] == dfn[u]) {
        int v;
        ++ cnt;
        do {
            v = s.top(); s.pop();
            id[v] = cnt;
        } while(u != v);
    }
}

int n, m, ans, vis[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v), add(u, v), tag[tot] = ++ *tag, add(v, u), tag[tot] = *tag;
    }
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = head[i] ; j ; j = rest[j]) {
            if(!vis[j]) {
                vis[j] = 1;
                if(id[i] != id[to[j]]) {
                    ++ deg[id[i]], ++ deg[id[to[j]]];
                }
            }
        }
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(deg[i] == 2) ++ ans;
    }
    printf("%d\n", (ans + 1) / 2);
}
