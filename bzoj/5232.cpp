#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 10;

int n, k;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int col_inp[N], col[N], tar[N];

int f[N][1 << 6], ans;

void dfs(int u, int fa) {
    // printf("u = %d, fa = %d\n", u, fa);
    f[u][1 << (col[u] - 1)] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        for(int s = (1 << k) - 1 ; ~ s ; -- s) {
            for(int t = 0 ; t < (1 << k) ; ++ t) {
                if(f[u][s] > n || f[v][t] > n) continue;
                f[u][s | t] = min(f[u][s | t], f[u][s] + f[v][t]);
            }
        }
    }
    ans = min(ans, f[u][(1 << k) - 1]);
}

int main() {
    srand((unsigned long long) new char);
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &col_inp[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    ans = n;
    for(int T = 50 ; T ; -- T) {
        for(int i = 1 ; i <= n ; ++ i) {
            tar[i] = rand() % k + 1;
        }
        for(int i = 1 ; i <= n ; ++ i) {
            col[i] = tar[col_inp[i]];
            memset(f[i], 0x3f, sizeof f[i]);
        }
        dfs(1, 0);
    }
    printf("%d\n", ans);
}
