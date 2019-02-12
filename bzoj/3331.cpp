#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n, m, q, head[N], rest[N], to[N], tot, sta[N], top, cnt, dfn[N], low[N], clk, sz[N];
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
struct E {
    int u, v;
} e[N];

void tarj(int u, int fa) {
    dfn[u] = low[u] = ++ clk;
    sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                ++ cnt;
                e[++ m] = (E) { u, cnt };
                int tmp;
                do {
                    tmp = sta[top --];
                    e[++ m] = (E) { tmp, cnt };
                } while(tmp != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int dep[N], sum[N], fa[N][25];
void getdep(int u, int fa) {
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i) {
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    }
    dep[u] = dep[fa] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        getdep(v, u);
    }
}
int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void dfs(int u, int fa) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sum[u] += sum[v];
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    while(m --) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    m = 0;
    cnt = n;
    tarj(1, 0);
    for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v;
        add(u, v), add(v, u);
    }
    getdep(1, 0);
    for(int i = 1 ; i <= q ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        int d = getlca(u, v);
        sum[u] ++;
        sum[v] ++;
        sum[d] --;
        sum[fa[d][0]] --;
    }
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", sum[i]);
    }
}
