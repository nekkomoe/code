#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

typedef long long ll;

int fa[N];

int get(int u) { return u == fa[u] ? u : fa[u] = get(fa[u]); }

int n, m;

ll x[N], y[N];

double ans;

struct E {
    int u, v;
    ll w;
} e[N * N];

bool operator < (E a, E b) {
    return a.w < b.w;
}

int done[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld", &x[i], &y[i]);
        fa[i] = i;
        for(int j = 1 ; j < i ; ++ j) {
            e[++ *fa] = (E) {i, j, (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])};
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        if(get(u) != get(v)) fa[get(u)] = get(v);
    }
    sort(e + 1, e + 1 + *fa);
    for(int i = 1 ; i <= *fa ; ++ i) {
        int u = e[i].u, v = e[i].v; ll w = e[i].w;
        if(get(u) != get(v)) {
            ans += sqrt(w);
            fa[get(u)] = get(v);
        }
    }
    printf("%.2lf\n", ans);
}
