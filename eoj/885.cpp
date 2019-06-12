#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 510, K = 60;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, k, a[N];
ll ans;
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

ll f[K][N][N]; // f[k][i][j]: 从i,j开始，走k轮后i<j的方案数
ll h[N][N];

struct PRESUM {
    ll S[N];
    ll & operator [] (int x) {
        return S[x];
    }
    void cls() {
        memset(S, 0, sizeof S);
    }
    void init() {
        for(int i = 1 ; i <= n ; ++ i) {
            upd(S[i], S[i - 1]);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            upd(S[i], S[i - 1]);
        }
    }
} row[N], col[N], h_row[N], h_col[N];

ll g(ll n) {
    return n * (n + 1) / 2;
}
void kano() {
    for(int t = 1 ; t <= k ; ++ t) {

        for(int i = 1 ; i <= n ; ++ i) {
            row[i].cls();
            for(int j = 1 ; j <= n ; ++ j) {
                row[i][j] = f[t - 1][i][j];
            }
            row[i].init();
        }

        for(int j = 1 ; j <= n ; ++ j) {
            col[j].cls();
            for(int i = 1 ; i <= n ; ++ i) {
                col[j][i] = f[t - 1][i][j];
            }
            col[j].init();
        }

        memset(h, 0, sizeof h);
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= n ; ++ j) {
                if(i - j >= 0) {
                    h[i][j] = f[t - 1][i][i - j];
                }
            }
        }

        for(int j = 1 ; j <= n ; ++ j) {
            h_col[j].cls();
            for(int i = 1 ; i <= n ; ++ i) {
                h_col[j][i] = h[i][j];
            }
            h_col[j].init();
        }


        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = i + 1 ; j <= n ; ++ j) {
                upd(f[t][i][j], f[t - 1][i][j] * (g(i - 1) + g(n - j) + g(j - i - 1)) % mod);
                upd(f[t][i][j], col[j][j - 1] - col[j][j - i - 1] - col[j][i - 1]);
                upd(f[t][i][j], row[i][n] - row[i][i + n - j] - row[i][j - 1] + row[i][i - 1]);
                upd(f[t][i][j], h_col[j - i][n] - h_col[j - i][n - i] - h_col[j - i][j - 1] + h_col[j - i][j - i - 1]);
            }
        }

        memset(h, 0, sizeof h);
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= n ; ++ j) {
                if(j - i >= 0) {
                    h[i][j] = f[t - 1][j - i][j];
                }
            }
        }

        for(int i = 1 ; i <= n ; ++ i) {
            h_row[i].cls();
            for(int j = 1 ; j <= n ; ++ j) {
                h_row[i][j] = h[i][j];
            }
            h_row[i].init();
        }

        for(int j = 1 ; j <= n ; ++ j) {
            for(int i = j + 1 ; i <= n ; ++ i) {
                upd(f[t][i][j], f[t - 1][i][j] * (g(j - 1) + g(n - i) + g(i - j - 1)) % mod);
                upd(f[t][i][j], row[i][i - 1] - row[i][i - j - 1] - row[i][j - 1]);
                upd(f[t][i][j], col[j][n] - col[j][j + n - i] - col[j][i - 1] + col[j][j - 1]);
                upd(f[t][i][j], h_row[i - j][n] - h_row[i - j][n - j] - h_row[i - j][i - 1] + h_row[i - j][i - j - 1]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            f[0][i][j] = 1;
        }
    }
    kano();
    ll all = pw((ll) n * (n + 1) / 2, k);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(a[i] < a[j]) {
                upd(ans, all - f[k][i][j]);
            } else {
                upd(ans, f[k][i][j]);
            }
        }
    }
    ans = ans * pw(pw((ll) n * (n + 1) / 2, k), mod - 2) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
}
