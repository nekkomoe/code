#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 }, N = 1e6 + 10;

int n, m, T, x;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
ll f[N];
void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) {
        f[rev(i, n)] = a[i];
    }
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2] * w % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) {
            a[i] = a[i] * inv % mod;
        }
    }
}
ll a[N], b[N], ans[N];

int main() {
    scanf("%d%d%d%d", &n, &m, &T, &x);

    for(int i = 1 ; i <= m ; ++ i) {
        int p; scanf("%d", &p);
        :: a[p] ++;
    }
    ll w = 1, wn = pw(3, (mod - 1) / x);
    for(int _ = 0 ; _ < x ; ++ _, w = w * wn % mod) {
        for(int i = 0 ; i < n ; ++ i) {
            b[i] = a[i] * w % mod;
        }
        b[0] ++;

        ntt(b, 0, n);
        for(int i = 0 ; i < n ; ++ i) {
            b[i] = pw(b[i], T);
        }
        ntt(b, 1, n);
        for(int i = 0 ; i < n ; ++ i) {
            ans[i] = (ans[i] + b[i]) % mod;
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        printf("%lld ", (ans[i] * pw(x, mod - 2) % mod + mod) % mod);
    }
}
