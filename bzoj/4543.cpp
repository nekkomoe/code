#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
vector<int> g[N];
int n;
int mxh[N], son[N];

void gmh(int u, int fa) {
    // for(int v: g[u]) {
    for(int t = 0 ; t < g[u].size() ; ++ t) {
        int v = g[u][t];
        if(v != fa) {
            gmh(v, u);
            if(mxh[v] > mxh[son[u]]) {
                son[u] = v;
            }
        }
    }
    mxh[u] = mxh[son[u]] + 1;
}

ll *f[N], *h[N], mem[N], *idx = mem, ans;

void dfs(int u, int fa) {
    if(son[u]) {
        f[son[u]] = f[u] + 1;
        h[son[u]] = h[u] - 1;
        dfs(son[u], u);
    }
    ans += h[u][0];
    f[u][0] = 1;
    // for(int v: g[u]) {
    for(int t = 0 ; t < g[u].size() ; ++ t) {
        int v = g[u][t];
        if(v != fa && v != son[u]) {
            f[v] = idx, idx += mxh[v] * 2;
            h[v] = idx, idx += mxh[v] * 2;
            dfs(v, u);
            for(int i = 0 ; i < mxh[v] ; ++ i) {
                ans += f[u][i - 1] * h[v][i]
                     + h[u][i + 1] * f[v][i];
            }
            for(int i = 0 ; i < mxh[v] ; ++ i) {
                h[u][i + 1] += f[u][i + 1] * f[v][i];
                h[u][i - 1] += h[v][i];
                f[u][i + 1] += f[v][i];
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    gmh(1, 0);
    f[1] = idx, idx += mxh[1] * 2;
    h[1] = idx, idx += mxh[1] * 2;
    dfs(1, 0);
    printf("%lld\n", ans);
}
