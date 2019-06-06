#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;

int n;
vector<int> g[N];
int dep[N], fa[N][22];
int getlca(int u, int v) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) {
        return u;
    }
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
             u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}
int rt;
vector<int> h[N];
void dfs(int u) {
    dep[u] = dep[fa[u][0]] + 1;
    h[dep[u]].push_back(u);
    for(int v: g[u]) {
        dfs(v);
    }
}
ll ans[N];

int a[N], b[N], c[N], top;

void sol(vector<int> &h) {
    top = 0;
    ll s = 0;
    for(int i = 0 ; i < h.size() ; ++ i) {
        if(i == 0) {
            top = 1;
            a[1] = h[0];
            b[1] = c[1] = 0;
        } else {
            while(1) {
                int lca = getlca(a[top], h[i]);
                if(b[top] <= dep[lca]) {
                    a[++ top] = h[i];
                    b[top] = dep[lca];
                    c[top] = i;
                    break;
                }
                s -= (ll) (c[top] - c[top - 1]) * b[top];
                -- top;
            }
            s += (ll) (c[top] - c[top - 1]) * b[top];
        }
        ans[h[i]] += s;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, f ; i <= n ; ++ i) {
        scanf("%d", &f);
        if(f) {
            fa[i][0] = f;
            g[f].push_back(i);
        } else {
            rt = i;
        }
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i <= n ; ++ i) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
    dfs(rt);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int u: h[i]) {
            ans[u] = ans[fa[u][0]] + i - 1;
        }
        sol(h[i]), reverse(h[i].begin(), h[i].end()), sol(h[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld ", ans[i]);
    }
}
