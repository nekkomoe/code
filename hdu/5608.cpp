#include "bits/stdc++.h"
using namespace std;
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e6, mod = 1e9 + 7;

ll ans, inv6, inv2, n;

int mu[N + 10], pri[N + 10], tot, S[N + 10], dn[N + 10], vis[N + 10], f[N + 10];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}

int h(ll n) {
    return (n * n % mod - 3 * n % mod + 2) % mod;
}

int H(ll n) {
    return (((
        n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod
    ) - (
        3 * n % mod * (1 + n) % mod * inv2 % mod
    )) % mod + (
        2 * n % mod
    )) % mod;
}

map<ll, ll> val;
ll F(ll n) {
    if(n <= N) return f[n];
    else if(val.find(n) != val.end()) return val[n];
    else {
        ll res = H(n);
        for(ll i = 2, j ; i <= n ; i = j + 1) {
            j = n / (n / i);
            res = (res - F(n / i) * (j - i + 1) % mod) % mod;
        }
        return val[n] = res;
    }
}

void sol() {
    scanf("%lld", &n);
    printf("%d\n", (F(n) % mod + mod) % mod);
}

int main() {
    inv6 = pw(6, mod - 2), inv2 = pw(2, mod - 2);
    mu[1] = 1;
    for(int i = 2 ; i <= N ; ++ i) {
        if(!vis[i]) pri[++ tot] = i, mu[i] = -1;
        for(int j = 1 ; j <= tot && i * pri[j] <= N ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
            mu[i * pri[j]] = -mu[i];
        }
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; i * j <= N ; ++ j) {
            f[i * j] = ((ll) f[i * j] + mu[j] * h(i) % mod) % mod;
        }
        f[i] = ((ll) f[i - 1] + f[i]) % mod;
    }
    int T; scanf("%d", &T); while(T --) sol();
}
