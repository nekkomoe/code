#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, mod = 19260817, pm1 = mod - 1;
typedef long long ll;

ll fac[N], invfac[N], f[N], mu[N];

int pri[N], tot, vis[N];

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

namespace getf {
    const int mod = pm1;
    void sol() {
        const int n = 1e6;
        for(int i = 1 ; i <= n ; ++ i) {
        	// [1, i): all 0
            for(int j = 1 ; j * i <= n ; ++ j) {
                // [j * i, (j + 1) * i)
                int l = j * i, r = min((j + 1) * i - 1, n);
                ll v = mu[i] * j * j % mod;
                f[l] += v, f[r + 1] -= v;
                f[l] %= mod, f[r + 1] %= mod;
            }
        }
        for(int i = 1 ; i <= n ; ++ i) {
        	f[i] = (f[i] + f[i - 1]) % mod;
        	if(f[i] < 0) f[i] += mod;
        }
    }
}

void init() {
    const int n = 1e6;
    fac[0] = 1; for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2), invfac[0] = 1;
    for(int i = n - 1 ; i ; -- i) invfac[i] = fac[i + 1] * (i + 1) % mod;

    mu[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) pri[++ tot] = i, mu[i] = -1;
        for(int j = 1 ; j <= tot && i * pri[j] <= n ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j]) mu[i * pri[j]] = -mu[i];
            else break;
        }
    }

    getf :: sol();
}

ll get(int n) {
    ll res = 1;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = res * pw(fac[j] * pw(fac[i - 1], mod - 2) % mod, f[n / i]) % mod;
    }
    return res;
}

ll sol() {
    int n; scanf("%d", &n);
    ll ans = pw(fac[n], 2 * n) * pw(pw(get(n), 2), mod - 2) % mod;
    return (ans % mod + mod) % mod;
}

int main() {
    init();
    int T; scanf("%d", &T);
    while(T --) printf("%lld\n", sol());
}