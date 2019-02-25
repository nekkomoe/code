#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 998244353;
int n; ll k;

ll a[N], b[N], f[N];
const int LEN = 262144;
int rev(int x) {
    int r = 0;
    for(int i = 0 ; (1 << i) < LEN ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
const int p = 998244353, g[2] = { 3, (p + 1) / 3};
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) {
        if(b & 1) {
            r = r * a % p;
        }
    }
    return r;
}
void ntt(ll *a, int ty) {
    for(int i = 0 ; i < LEN ; ++ i) f[rev(i)] = a[i];
    for(int i = 2 ; i <= LEN ; i <<= 1) {
        ll wn = pw(g[ty], (p - 1) / i);
        for(int j = 0 ; j < LEN ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % p;
                f[k] = (u + v) % p;
                f[k + i / 2] = (u - v) % p;
                w = w * wn % p;
            }
        }
    }
    for(int i = 0, inv = pw(LEN, p - 2) ; i < LEN ; ++ i) {
        a[i] = f[i];
        if(ty) a[i] = a[i] * inv % p;
    }
}

int main() {
    scanf("%d%lld", &n, &k), k %= mod;
    
    b[0] = 1, b[1] = k;
    for(int i = 2 ; i <= n ; ++ i)
        b[i] = (k + i - 1) * b[i - 1] % mod * pw(i, mod - 2) % mod;

    for(int i = 0 ; i < n ; ++ i)
        scanf("%lld", &a[i]);

    // for(int i = 0 ; i < n ; ++ i)
    //     for(int j = 0 ; j < n ; ++ j)
    //         (f[i + j] += a[i] * b[j] % mod) %= mod;
    // for(int i = 0 ; i < N ; ++ i) a[i] = f[i];

    ntt(a, 0), ntt(b, 0);
    for(int i = 0 ; i < LEN ; ++ i) {
        a[i] = a[i] * b[i] % mod;
    }
    ntt(a, 1);

    for(int i = 0 ; i < n ; ++ i)
        printf("%lld\n", (a[i] + mod) % mod);
}
