#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e6 + 10;

int n, m, head[N], rest[N], to[N], tot, sta[N], top, cnt, dfn[N], low[N], clk, sz[N];
ll ans[N];
vector<int> g[N];
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
void lk(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

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
                lk(u, cnt);
                int tmp;
                do {
                    tmp = sta[top --];
                    lk(tmp, cnt);
                } while(tmp != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void dfs(int u, int fa) {
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        ans[u] += 2ll * sz[v] * sz[u];
        sz[u] += sz[v];
    }
    sz[u] += u <= n;
    ans[u] += 2ll * (sz[u] - 1) * (n - sz[u]);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    cnt = n;
    tarj(1, 0);
    dfs(1, 0);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", ans[i] + 2 * (n - 1));
    }
}
