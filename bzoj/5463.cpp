#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int n, m, siz;

vector<int> g[N];

int dfn[N], low[N], clk, top, sta[N], w[N], cnt;

ll ans;

void lk(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

void tarj(int u, int fa) {
    dfn[u] = low[u] = ++ clk;
    sta[++ top] = u;
    w[u] = -1;
    ++ siz;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                w[++ cnt] = 1;
                lk(u, cnt);
                int tmp;
                do {
                    tmp = sta[top --];
                    lk(cnt, tmp);
                    ++ w[cnt];
                } while(tmp != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
int sz[N];
void dfs(int u, int fa) {
    ll cnt = 0;
    if(u <= n) {
        sz[u] = 1;
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        cnt += 2ll * sz[u] * sz[v];
        sz[u] += sz[v];
    }
    cnt += 2ll * sz[u] * (siz - sz[u]);
    ans += w[u] * cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    cnt = n;
    for(int i = 1 ; i <= n ; ++ i) {
        if(!dfn[i]) {
            siz = 0;
            tarj(i, 0);
            dfs(i, 0);
            // assert(top == 0);
        }
    }
    printf("%lld\n", ans);
}
