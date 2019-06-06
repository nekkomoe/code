#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e6 + 3, N = 2 * mod + 110;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll fac[N], inv[N], invfac[N];

int main() {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i < mod ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[mod - 1] = pw(fac[mod - 1], mod - 2);
    for(int i = mod - 2 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }

    inv[1] = 1;
    for(int i = 2 ; i < mod ; ++ i) {
        inv[i] = (-(mod / i) * inv[mod % i] % mod + mod) % mod;
    }
    int q; scanf("%d", &q);
    while(q --) {
        ll x, d, n;
        scanf("%lld%lld%lld", &x, &d, &n);
        if(d == 0) {
            printf("%lld\n", pw(x, n));
        } else if(n >= mod || !x) {
            puts("0");
        } else {
            x = x * inv[d] % mod;
            // x * (x + 1) * ... * (x + n - 1)
            // printf("%lld\n", x + n - 1);
            if(x + n - 1 >= mod) {
                puts("0");
            } else {
                printf("%lld\n", fac[x + n - 1] * invfac[x - 1] % mod * pw(d, n) % mod);
            }
        }
    }
}
