#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2010, mod = 1e9 + 7;

ll fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll S[N], n, k, r;

namespace ziranshumihe {
    ll _f[N], f[N];
    
    ll fac[N], invfac[N], pre[N], sub[N];
    
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
    
    void sol() {
        for(int i = 1 ; i <= k + 2 ; ++ i) {
            _f[i] = (_f[i - 1] + pw(i, k)) % mod;
        }
        for(int i = 0 ; i <= k + 1 ; ++ i) {
            f[i] = _f[i + 1];
        }
        
        fac[0] = invfac[0] = 1;
        for(int i = 1 ; i <= k + 2 ; ++ i) {
            fac[i] = fac[i - 1] * i % mod;
        }
        invfac[k + 2] = pw(fac[k + 2], mod - 2);
        for(int i = k + 1 ; i ; -- i) {
            invfac[i] = invfac[i + 1] * (i + 1) % mod;
        }
        printf("%lld\n", sol(n, k + 1));
    }

}

void sol() {
    scanf("%lld%lld", &n, &k);
    r = k;
    r %= mod;
    if(r == 1) {
        ziranshumihe :: sol();
    } else {
        S[0] = (pw(r, n + 1) - r) % mod * pw(r - 1, mod - 2) % mod;
        for(int k = 1 ; k <= :: k ; ++ k) {
            ll s = (pw(n, k) * pw(r, n + 1) % mod - r) % mod;
            for(int j = 0 ; j < k ; ++ j) {
                s += C(k, j) * ((k - j) % 2 == 0 ? 1 : -1) % mod * ((S[j] - r) % mod) % mod;
                s %= mod;
            }
            S[k] = s * pw(r - 1, mod - 2) % mod;
        }
        printf("%lld\n", (S[k] % mod + mod) % mod);
    }
}

int main() {
    const int n = 2000;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    sol();
}

