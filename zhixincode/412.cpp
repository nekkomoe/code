#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
const ll inv2 = pw(2, mod - 2);

int tra[100], n;

ll a[1 << 22], cnt[100];

void fwt(ll *a, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = a[k], v = a[k + i / 2];
                if(ty == 0) a[k] = (u + v) % mod, a[k + i / 2] = (u - v) % mod;
                else a[k] = (u + v) * inv2 % mod, a[k + i / 2] = (u - v) * inv2 % mod;
            }
        }
    }
}

int main() {
    tra[0] = 0;
    tra[1] = 1;
    tra[2] = 4;
    tra[3] = 1;
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        int pos = 0;
        for(int j = 1, x ; j <= 10 ; ++ j) {
            scanf("%d", &x);
            pos = (pos << 2) | x;
        }
        ++ a[pos];
    }

    n = 1 << 20;

    fwt(a, n, 0);
    for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * a[i] % mod;
    fwt(a, n, 1);

    for(int i = 0 ; i < n ; ++ i) {
        int pos = 0, x = i;
        for(int j = 0 ; j < 10 ; ++ j) {
            pos += tra[x & 3];
            x >>= 2;
        }
        (cnt[pos] += a[i]) %= mod;
    }

    ll ans = 0;
    for(int i = 0 ; i < 100 ; ++ i) {
        ans = (ans + cnt[i] * cnt[i] % mod) % mod;
    }
    if(ans < 0) ans += mod;
    printf("%lld\n", ans);
}
