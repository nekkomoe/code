#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, Q = 5010;
int n, q, a[N], mx[N][22];

struct S {
    int l, r, mx; double p;
} s[N];
int getmx(int l, int r) {
    int res = 0;
    for(int i = 20 ; ~ i ; -- i) {
        if(l + (1 << i) - 1 <= r) {
            res = max(res, mx[l][i]);
            l += 1 << i;
        }
    }
    return res;
}
double f[Q][Q];
int sz[Q];
vector<int> g[Q];
void dfs(int u) {
    // printf("vis %d\n", u);
    sz[u] = 1;
    for(int v: g[u]) {
        dfs(v);
        sz[u] = max(sz[u], sz[v] + 1);
    }
    for(int i = 0 ; i <= sz[u] ; ++ i) {
        double p = i ? s[u].p : 0, q = 1 - s[u].p;
        for(int v: g[u]) {
            int tmp = i + s[u].mx - s[v].mx - 1;
            if(tmp >= 0) {
                p *= f[v][min(:: q + 1, tmp)];
            }
            q *= f[v][min(:: q + 1, tmp + 1)];
        }
        f[u][i] = p + q;
    }
    for(int i = sz[u] + 1 ; i <= q + 1 ; ++ i) {
        f[u][i] = 1;
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        mx[i][0] = a[i];
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
    for(int i = 1 ; i <= q ; ++ i) {
        scanf("%d%d%lf", &s[i].l, &s[i].r, &s[i].p);
        s[i].mx = getmx(s[i].l, s[i].r);
    }

    s[++ q] = (S) { 1, n, getmx(1, n), 0 };

    // for(int i = 1 ; i <= q ; ++ i) {
        // printf("%d\n", s[i].mx);
    // }

    sort(s + 1, s + 1 + q, [&] (S a, S b) { return a.l == b.l ? a.r > b.r : a.l < b.l; });
    for(int i = 1 ; i <= q ; ++ i) {
        for(int j = i - 1 ; j >= 1 ; -- j) {
            if(s[j].l <= s[i].l && s[i].r <= s[j].r) {
                // printf("%d -> %d\n", j, i);
                g[j].emplace_back(i);
                break;
            }
        }
    }
    dfs(1);
    // for(int i = 0 ; i <= sz[1] ; ++ i) {
        // printf("%.2lf\n", f[1][i]);
    // } puts("");
    double ans = f[1][0] * s[1].mx;
    for(int i = 1 ; i <= sz[1] ; ++ i) {
        ans += (f[1][i] - f[1][i - 1]) * (s[1].mx + i);
    }
    printf("%.10lf\n", ans);
}
