#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1000000007, N = 1e6 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, m, u[N], d[N], vis[N];

ll inv[N], fac[N], invfac[N];

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    scanf("%d%d", &n, &m);
    if(n == 1) {
        puts("1");
        return 0;
    }
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &u[i], &d[i]);
        inv[i] = invfac[d[i] - 1];
    }
    ll ans = 0;
    for(int s = 0 ; s < (1 << m) ; ++ s) {
        int cnt = 0;
        ll sum = 0, prod = 1;
        for(int i = 1 ; i <= m ; ++ i) {
            if(s & (1 << (i - 1))) {
                if(vis[u[i]]) {
                    cnt = -1;
                    break;
                }
                vis[u[i]] = 1;
                ++ cnt;
                sum += d[i] - 1;
                prod = prod * inv[i] % mod;
            }
        }
        for(int i = 1 ; i <= m ; ++ i) {
            if(s & (1 << (i - 1))) {
                vis[u[i]] = 0;
            }
        }
        if(cnt == -1) continue;
        ll val = 0;
        if(sum <= n - 2) {
            val = C(n - 2, sum) * pw(n - cnt, n - 2 - sum) % mod * fac[sum] % mod * prod % mod;
        }
        ans = (ans + (cnt & 1 ? -1 : 1) * val) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
