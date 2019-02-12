#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 300;

ll n, m, K, f[N][2][2];

int tot_n, tot_m, dig_n[N], dig_m[N];

void runprog() {
    scanf("%lld%lld", &n, &m);
    m = min(n, m);
    ll ans = (1 + m % mod) * (m % mod) % mod * 500000004 % mod;
    ans = (ans + (m % mod + 1) * ((n % mod) - (m % mod) + 1) % mod) % mod;
    tot_n = tot_m = 0;
    for( ; n ; n /= K, m /= K) {
        dig_n[++ tot_n] = n % K;
        dig_m[++ tot_m] = m % K;
    }
    memset(f, 0, sizeof f), f[tot_n + 1][1][1] = 1;
    for(int i = tot_n ; i ; -- i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            for(int k = 0 ; k < 2 ; ++ k) {
                if(f[i + 1][j][k]) {
                    for(int x = 0 ; x <= (j ? dig_n[i] : K - 1) ; ++ x) {
                        for(int y = 0 ; y <= (k ? dig_m[i] : K - 1) && y <= x ; ++ y) {
                            (f[i][j & (x == dig_n[i])][k & (y == dig_m[i])] += f[i + 1][j][k]) %= mod;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            ans = (ans - f[1][i][j]) % mod;
        }
    }
    if(ans < 0) ans += mod;
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d%lld", &t, &K);
    while(t --) {
        runprog();
    }
}
