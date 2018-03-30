%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

const int N = 100000 * 2 + 10;

int head[N], rest[N], to[N], w[N], tot, n, m, deg[N];

double s[N], f[N], g[N], ans;

void add(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}

queue<int> q;

int u[N], v[N], c[N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c), u ++, v ++;
        :: u[i] = u, :: v[i] = v, :: c[i] = c;
        s[u] += c;
        add(v, u, c);
        deg[u] ++;
    }
    for(int i = 1 ; i <= n ; ++ i) if(!deg[i]) q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            deg[v] --, f[v] += (f[u] + 1) * w[i] / s[v];
            if(!deg[v]) q.push(v);
        }
    }
    memset(head, 0, sizeof head), tot = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int u = :: u[i], v = :: v[i], c = :: c[i];
        add(u, v, c);
        deg[v] ++;
    }
    for(int i = 1 ; i <= n ; ++ i) if(!deg[i]) q.push(i);
    g[1] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            deg[v] --, g[v] += g[u] * w[i] / s[u];
            if(!deg[v]) q.push(v);
        }
    }
    ans = f[1];
    for(int i = 1 ; i <= m ; ++ i) {
        int u = :: u[i], v = :: v[i], c = :: c[i];
        double g = (f[u] - (f[v] + 1) * c / s[u]) * s[u] / (s[u] - c) - f[u];
        ans = max(ans, f[1] + g * :: g[u]);
    }
    printf("%.6lf\n", ans);
}

