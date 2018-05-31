#include <bits/stdc++.h>

using namespace std;

const int N = 6e5 + 10;

int head[N], rest[N * 2], to[N * 2], w[N * 2], tot;

void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}

int n, k;

typedef long long ll;
typedef pair<ll, ll> p;
const ll inf = 3e11;

p operator + (p a, p b) { return p(a.first + b.first, a.second + b.second); }
p operator - (p a, p b) { return p(a.first - b.first, a.second - b.second); }

p f[N], g[N];
ll l = -inf, r = inf, mid, ans;

void dfs(int u, int fa) {
    p sumg(0, 0), mxf(-inf, 0), preg(0, 0);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sumg = sumg + g[v];
    }
    g[u] = sumg;
    f[u] = p(-mid, 1) + sumg;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i], w = :: w[i];
        if(v == fa) continue;
        mxf = max(mxf, sumg - g[v] + f[v] + p(w, 0));
    }
    f[u] = max(f[u], mxf);
    mxf = p(-inf, 0);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i], w = :: w[i];
        if(v == fa) continue;
        sumg = sumg - g[v];
        g[u] = max(g[u], mxf + f[v] + p(w + mid, -1) + sumg);
        mxf = max(mxf + g[v], preg + f[v] + p(w, 0));
        preg = preg + g[v];
    }
    g[u] = max(g[u], f[u]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
#endif
    scanf("%d%d", &n, &k), ++ k;
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    while(l <= r) {
        mid = (l + r) >> 1;
        dfs(1, 0);
        if(g[1].second >= k) ans = g[1].first + k * mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n", ans);
}
