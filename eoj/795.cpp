#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 21, mod = 1e9 + 7;

void upd(int &x, int y) {
    x = ((ll) x + y) % mod;
    if(x < 0) x += mod;
}

int g_sta[N], cnt[1 << N], saf[1 << N], n, m, g[N][1 << N], f[N][1 << N], lim;

void fmt(int *f, int g) {
    for(int i = 0 ; i < n ; ++ i) {
        for(int j = 0 ; j < lim ; ++ j) {
            if((j >> i) & 1) {
                upd(f[j], g * f[j - (1 << i)]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    lim = 1 << n;
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        g_sta[u] |= 1 << (v - 1);
        g_sta[v] |= 1 << (u - 1);
    }
    for(int i = 0 ; i < (1 << n) ; ++ i) {
        cnt[i] = cnt[i >> 1] + (i & 1);
        int s = 0, flag = 1;
        for(int j = 1 ; j <= n ; ++ j) {
            if((i >> (j - 1)) & 1) {
                s |= g_sta[j];
            }
        }
        for(int j = 1 ; j <= n ; ++ j) {
            if((i >> (j - 1)) & 1) {
                if((s >> (j - 1)) & 1) {
                    flag = 0;
                    break;
                }
            }
        }
        saf[i] = flag;
        g[cnt[i]][i] = ((cnt[i] + 1) & 1 ? -1 : 1) * saf[i];
    }
    for(int i = 0 ; i <= n ; ++ i) {
        fmt(g[i], 1);
    }
    f[0][0] = 1;
    fmt(f[0], 1);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < i ; ++ j) {
            for(int s = 0 ; s < lim ; ++ s) {
                upd(f[i][s], (ll) f[j][s] * g[i - j][s] % mod);
            }
        }

        fmt(f[i], -1);
        for(int s = 0 ; s < lim ; ++ s) {
            if(cnt[s] != i) {
                f[i][s] = 0;
            }
        }
        if(i < n) {
            fmt(f[i], 1);
        }
    }
    printf("%d\n", f[n][(1 << n) - 1]);
}
