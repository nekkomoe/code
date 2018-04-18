#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

struct E {
    int u, v, w;
} e[N * N];

bool operator < (E a, E b) {
    return a.w < b.w;
}

int n, c[N][N], tp;

int fa[N];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

long long ans;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        fa[i] = i;
        for(int j = i ; j <= n ; ++ j) {
            scanf("%d", &c[i][j]);
            e[++ tp] = (E) { i - 1, j, c[i][j] };
        }
    }
    sort(e + 1, e + 1 + tp);
    for(int i = 1 ; i <= tp ; ++ i) {
        int u = e[i].u, v = e[i].v;
        if(get(u) != get(v)) {
            fa[get(u)] = get(v);
            ans += e[i].w;
        }
    }
    printf("%lld\n", ans);
}
