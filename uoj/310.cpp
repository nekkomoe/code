// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1 << 20, mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll inv2 = pw(2, mod - 2);

int n; ll a[N];

void fwt(ll *f, int n, int ty) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j + i / 2 < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty == 0) f[k] = (u + v) % mod, f[k + i / 2] = (u - v) % mod;
                else f[k] = (u + v) * inv2 % mod, f[k + i / 2] = (u - v) * inv2 % mod;
            }
        }
    }
}

ll pw1[N], pw3[N];

int main() {
    pw1[0] = pw3[0] = 1;
    for(int i = 1 ; i < N ; ++ i) {
        pw1[i] = pw1[i - 1] * (-1) % mod;
        pw3[i] = pw3[i - 1] * 3 % mod;
    }
    ll inv4 = pw(4, mod - 2);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        a[0] ++, a[x] += 2;
    }
    fwt(a, N, 0);
    for(int i = 0 ; i < N ; ++ i) {
        int x = (3ll * n - a[i]) % mod * inv4 % mod;
        a[i] = pw1[x] * pw3[n - x] % mod;
    }
    fwt(a, 1048576, 1);
    ll ans = a[0] - 1;
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
