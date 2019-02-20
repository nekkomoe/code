#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1000000007, N = 17;

int n, c[N][N];

ll f[1 << N], g[1 << N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%d", &c[i][j]);
        }
    }

    for(int s = 0 ; s < (1 << n) ; ++ s) {
        g[s] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            if(s & (1 << (i - 1))) {
                for(int j = 1 ; j < i ; ++ j) {
                    if(s & (1 << (j - 1))) {
                        (g[s] *= c[i][j] + 1) %= mod;
                    }
                }
            }
        }
    }

    for(int s = 0 ; s < (1 << n) ; ++ s) {
        f[s] = g[s];
        for(int t = s ; t ; t = (t - 1) & s) {
            if(t != s && (t & (s & (-s)))) {
                (f[s] -= f[t] * g[s - t] % mod) %= mod;
            }
        }
    }

    printf("%lld\n", (f[(1 << n) - 1] + mod) % mod);
}
