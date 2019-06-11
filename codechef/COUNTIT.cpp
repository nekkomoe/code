#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, mod = 1e9 + 7;

ll _f[N], f[N], n, k;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll fac[N], invfac[N], pre[N], sub[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

ll sol(ll x, ll n) {
    for(ll i = 0 ; i <= n ; ++ i) {
        if(i == 0) pre[i] = 1;
        else pre[i] = pre[i - 1];
        pre[i] = pre[i] * (x % mod - (i + 1)) % mod;
    }
    for(ll i = n ; i >= 0 ; -- i) {
        if(i == n) sub[i] = 1;
        else sub[i] = sub[i + 1];
        sub[i] = sub[i] * (x % mod - (i + 1)) % mod;
    }
    ll res = 0;
    for(ll i = 0, poi ; i <= n ; ++ i) {
        poi = (i == 0 ? 1 : pre[i - 1]) * (i == n ? 1 : sub[i + 1]) % mod;
        res = (res + f[i] * poi % mod * invfac[i] % mod * invfac[n - i] % mod * ((n - i) % 2 ? -1 : 1) % mod) % mod;
    }
    return (res + mod) % mod;
}

int main() {
    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k);
        int lim = n + m + 10;
        for(int i = 1 ; i <= lim ; ++ i) {
            int x = i;
            ll tmp = ((pw(x, n) - pw(x - 1, n)) % mod) * ((pw(x, m) - pw(x - 1, m)) % mod) % mod;
            _f[i] = (_f[i - 1] + tmp) % mod;
        }
        for(int i = 0 ; i <= lim - 1 ; ++ i) {
            f[i] = _f[i + 1];
        }
        printf("%lld\n", sol(k, lim - 1));
    }
}
