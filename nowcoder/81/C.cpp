#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int n, m, cnt;

int dfn[N], low[N], ins[N], mn[N];

stack<int> s;

vector<int> bel[N];

int id[N];

void dfs(int u) {
    static int clk = 0;
    dfn[u] = low[u] = ++ clk;
    s.push(u), ins[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            dfs(v), low[u] = min(low[u], low[v]);
        } else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int v;
        mn[++ cnt] = n;
        do {
            v = s.top(); s.pop(); ins[v] = 0;
            bel[cnt].push_back(v), mn[cnt] = min(mn[cnt], v);
            id[v] = cnt;
        } while(u != v);
    }
}

int deg[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        for(int j = 0 ; j < bel[i].size() ; ++ j) {
            int u = bel[i][j];
            for(int k = head[u] ; k ; k = rest[k]) {
                if(id[to[k]] != id[u]) {
                    deg[id[to[k]]] = 1;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(deg[i] == 0) ++ ans;
    }
    printf("%d\n", ans);
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(deg[i] == 0) {
            printf("%d", mn[i]);
            if(-- ans) putchar(' ');
        }
    }
}
