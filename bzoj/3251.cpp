#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, q;

int head[N], rest[N], to[N], tot, e[N], deep[N], fa[N];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
    deep[u] = deep[fa[u]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
        }
    }
}

int sta[N], tp;

void solve(int u, int v) {
    tp = 0;
    while(tp < 50 && u != v) {
        if(deep[u] > deep[v]) sta[++ tp] = e[u], u = fa[u];
        else sta[++ tp] = e[v], v = fa[v];
    }
    sta[++ tp] = e[u];
    if(tp >= 50) return puts("Y"), void();
    sort(sta + 1, sta + 1 + tp);
    for(int i = 1 ; i <= tp - 2 ; ++ i) {
        if((long long) sta[i] + sta[i + 1] > sta[i + 2]) {
            return puts("Y"), void();
        }
    }
    puts("N");
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &e[i]);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1);
    for(int i = 1, t, u, v ; i <= q ; ++ i) {
        scanf("%d%d%d", &t, &u, &v);
        if(!t) solve(u, v);
        else e[u] = v;
    }
}
