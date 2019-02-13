#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e6 + 10;

int n, cnt, head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

vector<pair<int, int> > e;

int dfn[N], low[N], clk, sta[N], top;

int neko(int u, int fa) {
    dfn[u] = low[u] = ++ clk, sta[++ top] = u;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            neko(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                e.push_back(make_pair(u, ++ cnt));
                int cat;
                do {
                    cat = sta[top --];
                    e.push_back(make_pair(cat, cnt));
                } while(cat != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int a, b, fa[N][30], val[N], dep[N];

void dfs(int u, int fa) {
    :: fa[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for(int i = 1 ; i <= 20 ; ++ i) {
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
    }
}

int get(int u, int v) {
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

int main() {
    scanf("%d", &n), cnt = n;
    while(1) {
        int u, v; scanf("%d%d", &u, &v);
        if(u == 0) break;
        add(u, v), add(v, u);
    }
    neko(1, 0);
    for(int i = 1 ; i <= n ; ++ i) head[i] = 0; tot = 0;
    for(int i = 0 ; i < e.size() ; ++ i) {
        int u = e[i].first, v = e[i].second;
        add(u, v), add(v, u);
    }
    scanf("%d%d", &a, &b);
    int inpa = a, inpb = b;
    dfs(1, 0);
    int ans = n + 10;
    int lca = get(a, b);
    if(lca <= n && lca != a && lca != b) {
        ans = lca;
    }
    while(a) {
        val[a] ^= 1;
        a = fa[a][0];
    }
    while(b) {
        val[b] ^= 1;
        b = fa[b][0];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(val[i] == 1 && i != inpa && i != inpb) {
            ans = min(ans, i);
            break;
        }
    }
    if(ans <= n) printf("%d\n", ans);
    else puts("No solution");
}
