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
//        ll pro = 1;
//        for(ll j = 0 ; j <= n ; ++ j) {
//            if(i != j) {
//                pro = pro * (x % mod - (j + 1)) % mod;
//                pro = pro * pw(i - j, mod - 2) % mod; 
//            }
//        } 
//        res = (res + f[i] * pro % mod) % mod;
    }
    return (res + mod) % mod;
}

void poi() {
    cin >> n >> k;
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
    cout << sol(n, k + 1) << endl;
}

int main() {
    ios :: sync_with_stdio(0);
    int T; cin >> T;
    while(T --) poi();
}
