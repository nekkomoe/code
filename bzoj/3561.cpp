#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e5, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}

int vis[N + 10], p[N + 10], tot, pws[N + 10], sum[N + 10], n, m, mu[N + 10];

int main() {
    scanf("%d%d", &n, &m); if(n > m) swap(n, m);
    mu[1] = pws[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) mu[i] = -1, p[++ tot] = i;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= N ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
        pws[i] = 1;
    }
    int ans = 0;
    for(int d = 1 ; d <= n ; ++ d) {
        int cnt = 0;
        for(int i = 1 ; i <= m / d ; ++ i) {
            pws[i] = (ll) pws[i] * i % mod;
            sum[i] = ((ll) pws[i] + sum[i - 1]) % mod;
        }
        for(int x = 1 ; x <= n / d ; ++ x) {
            cnt = ((ll) cnt + (ll) mu[x] * pws[x] % mod * pws[x] % mod * sum[n / d / x] % mod * sum[m / d / x] % mod) % mod;
        }
        ans = (ans + (ll) pw(d, d) * cnt % mod) % mod;
    }
    printf("%d\n", (ans % mod + mod) % mod);
}
