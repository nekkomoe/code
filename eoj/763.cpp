#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 110, mod = 998244353;
ll p[N][N][5];

int n, m, k;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll f[2][12 * 3];

int main() {
//    freopen("songfenti.in", "r", stdin);
//    freopen("songfenti.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            for(int t = 1 ; t <= 3 ; ++ t) {
                scanf("%lld", &p[i][j][t]);
                (p[i][j][t] *= pw(int(1e8), mod - 2)) %= mod;
            }
        }
    }
    ll ans = 0;

    for(int u = 1 ; u <= n ; ++ u) {
        for(int v = u + 1 ; v <= n ; ++ v) {
            memset(f, 0, sizeof f);
            int cur = 0;
            f[cur][0] = 1;
            for(int i = 1 ; i <= m ; ++ i) {
                cur ^= 1;
                memset(f[cur], 0, sizeof f[cur]);
                for(int j = 0 ; j <= 3 * m ; ++ j) {
                    for(int a = 1 ; a <= 3 ; ++ a) {
                        for(int b = 1 ; b <= 3 ; ++ b) {
                            int del = abs(a - b);
                            if(j >= del) {
                                ll coef = p[u][i][a] * p[v][i][b] % mod;
                                (f[cur][j] += f[!cur][j - del] * coef % mod) %= mod;
                            }
                        }
                    }
                }
            }
            for(int i = 0 ; i <= 3 * m ; ++ i) {
                (ans += f[cur][i] * pw(i, k) % mod) %= mod;
            }
        }
    }

    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
