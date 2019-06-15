#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7, N = 1e5 + 10;

int pw(int a, int b) {
    int r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int getinv(int n) {
    return pw(n, mod - 2);
}

int C[30][30];
int f[1ll << 22];
void upd(int &x, int y) {
    x = (x + y) % mod;
}
int g[1ll << 22]; // 这个集合内随便连边的方案数
int n;

namespace NEKO {
    int g[22][1ll << 22];
    int f[22][1ll << 22];
    int lim;

    void fmt(int *f, int g) {
        if(g == 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < lim; ++j) {
                    if ((j >> i) & 1) {
                        upd(f[j], f[j - (1 << i)]);
                    }
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < lim; ++j) {
                    if ((j >> i) & 1) {
                        upd(f[j], -f[j - (1 << i)]);
                    }
                }
            }
        }
    }

    void neko() {
        lim = 1 << n;
        for(int s = 0 ; s < (1 << n) ; ++ s) {
            g[__builtin_popcount(s)][s] = :: g[s];
        }

        for (int i = 0; i <= n; ++i) {
            fmt(g[i], 1);
        }
        f[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                for (int s = 0; s < lim; ++s) {
                    upd(f[i][s], (long long) -f[j][s] * g[i - j][s] % mod);
                }
            }
            fmt(f[i], -1);
            for(int s = 0 ; s < lim ; ++ s) {
                int c = __builtin_popcount(s);
                if(c != i) {
                    f[i][s] = 0;
                }
                if(c == i) {
                    if(!(s & 1)) {
                        f[i][s] = 0;
                    } else {
                        upd(f[i][s], :: g[s]);
                    }
                }
            }
            fmt(f[i], 1);
        }
        fmt(f[n], -1);
        int ans = (f[n][(1 << n) - 1] % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i < n ; ++ i) {
        for(int j = 1 ; j <= n - i ; ++ j) {
            int k; scanf("%d", &k);
            C[i][i + j] = C[i + j][i] = k;
        }
    }
    for(int s = 0 ; s < (1 << n) ; ++ s) {
        g[s] = 1;
        for(int x = 1 ; x <= n ; ++ x) {
            if((s >> (x - 1)) & 1) {
                for(int y = x ; y <= n ; ++ y) {
                    if((s >> (y - 1)) & 1) {
                        g[s] = (long long) g[s] * (C[x][y] + 1) % mod;
                    }
                }
            }
        }
    }

    NEKO :: neko();

    // f[0] = 1;
    // for(int s = 1 ; s < (1 << n) ; ++ s) {
    //     if(!(s & 1)) continue;
    //     f[s] = g[s];
    //     for(int t = s ; t ; t = (t - 1) & s) {
    //         if(t == s) continue;
    //         upd(f[s], -f[t] * g[s - t] % mod);
    //     }
    // }
    // printf("%lld\n", (f[(1 << n) - 1] % mod + mod) % mod);
}
