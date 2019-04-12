#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, MOD = 1e9 - 401, phimod = MOD - 1, M[4] = { 2, 13, 5281, 7283 };

ll mod; int ty;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, m;
ll ans[4];
ll fac[4][N];

pair<ll, ll> get(ll n) {
    // n = mod^first * second
    if(!n) return make_pair(0, 1);
    ll x = n / mod, y = n / mod, res = 1;
    if(y) {
        for(ll i = 2 ; i < mod ; ++ i) {
            if(i % mod) {
                res = res * i % mod;
            }
        }
        res = pw(res, y);
    }
    for(ll i = y * mod + 1 ; i <= n ; ++ i) {
        if(i % mod) {
            res = res * i % mod;
        }
    }
    auto tmp = get(x);
    return make_pair(tmp.first + x, res * tmp.second % mod);
}

ll calc(ll d) {
    auto a = get(n);
    auto b = get(n / d);
    auto c = get(d);
    return pw(mod, a.first - b.first - n / d * c.first) * a.second % mod
    * pw(b.second, mod - 2) % mod
    * pw(pw(c.second, mod - 2), n / d) % mod;
}
ll getans() {
    ll res = 0;
    for(ll i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            res = (res + calc(i)) % mod;
            if(i != n / i) {
                res = (res + calc(n / i)) % mod;
            }
        }
    }
    return res;
}

ll merge() {
    ll res = 0;
    for(int i = 0 ; i < 4 ; ++ i) {
        ll m1 = phimod / M[i];
        mod = M[i];
        res = (res + pw(m1, M[i] - 2) * m1 % phimod * ans[i] % phimod) % phimod;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < 4 ; ++ i) {
        fac[i][0] = 1;
    }
    for(int i = 1 ; i <= int(1e6) ; ++ i) {
        for(int j = 0 ; j < 4 ; ++ j) {
            fac[j][i] = fac[j][i - 1] * i % M[j];
        }
    }
    for(int i = 0 ; i < 4 ; ++ i) {
        mod = M[i];
        ty = i;
        ans[i] = getans();
    }
    ll val = merge();
    mod = MOD;
    printf("%lld\n", pw(m, val));
}
