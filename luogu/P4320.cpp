// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int read() {
    int x = 0, c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x; 
}

const int N = 1e6 + 10, M = 4 * N;

int n, m, q, cnt, head[N], rest[M], to[M], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

struct E { int u, v; } e[M]; int inu;

int dfn[N], low[N], clk, sta[N], top;

void neko(int u, int fa) {
    dfn[u] = low[u] = ++ clk, sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            neko(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                e[++ inu] = (E) { u, ++ cnt };
                int cat;
                do {
                    cat = sta[top --];
                    e[++ inu] = (E) { cat, cnt };
                } while(cat != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int dep[N], sum[N], tp[N], son[N], sz[N], fa[N];

void dfs(int u, int fa) {
    :: fa[u] = fa;
    dep[u] = dep[fa] + 1;
    sum[u] = sum[fa] + (u <= n);
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}

void nya(int u, int t) {
    tp[u] = t;
    if(son[u]) {
        nya(son[u], t); 
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u] || v == son[u]) continue;
        nya(v, v);
    }
}

int get(int u, int v) {
    while(tp[u] != tp[v]) {
        if(dep[tp[u]] < dep[tp[v]]) swap(u, v);
        u = fa[tp[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    n = cnt = read(), m = read(); 
    while(m --) {
        int u = read(), v = read(); 
        add(u, v), add(v, u);
    }
    neko(1, 0);
    for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
    for(int i = 1 ; i <= inu ; ++ i) {
        int u = e[i].u, v = e[i].v;
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    nya(1, 1);
    q = read();
    while(q --) {
        int u = read(), v = read();
        int d = get(u, v);
        printf("%d\n", sum[u] + sum[v] - sum[d] - sum[fa[d]]);
    }
}
