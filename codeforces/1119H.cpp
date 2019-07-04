#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 2e6 + 10, inv2 = (mod + 1) / 2;

ll pw(ll a, ll b) {
    if(b < 0) {
        return pw(a, -b);
    }
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

void fwt(ll *f, int ty, int n) {
    for(int i = 2 ; i <= n ; i <<= 1) {
        for(int j = 0 ; j < n ; j += i) {
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2];
                if(ty) {
                    f[k] = (u + v) % mod * inv2 % mod;
                    f[k + i / 2] = (u - v) % mod * inv2 % mod;
                } else {
                    f[k] = (u + v) % mod;
                    f[k + i / 2] = (u - v) % mod;
                }
            }
        }
    }
}
int n, x, y, z, k;
ll f[N], g[N], h[N], ans[N];
int main() {
    scanf("%d%d", &n, &k);
    k = 1 << k;
    scanf("%d%d%d", &x, &y, &z);
    int sum = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        sum ^= a;
        ++ f[a ^ b];
        ++ g[a ^ c];
        ++ h[b ^ c];
    }
    fwt(f, 0, k), fwt(g, 0, k), fwt(h, 0, k);
    int inv4 = (ll) inv2 * inv2 % mod;
    for(int i = 0 ; i < k ; ++ i) {
        int a = ((ll) n + f[i] + g[i] + h[i]) * inv4 % mod;
        int b = ((ll) n + f[i] - g[i] - h[i]) * inv4 % mod;
        int c = ((ll) n - f[i] + g[i] - h[i]) * inv4 % mod;
        int d = ((ll) n - f[i] - g[i] + h[i]) * inv4 % mod;
        ans[i] = pw((ll) x + y + z, a) * pw((ll) x + y - z, b) % mod * pw((ll) x - y + z, c) % mod * pw((ll) x - y - z, d) % mod;
    }
    fwt(ans, 1, k);
    for(int i = 0 ; i < k ; ++ i) {
        printf("%lld ", (ans[i ^ sum] % mod + mod) % mod);
    }
}
