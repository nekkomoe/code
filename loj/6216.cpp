#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, mod;

ll f[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll fac[N], invfac[N];

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[n - m] % mod * invfac[m] % mod;
}

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    for(int i = 2 ; i <= n ; ++ i) {
        f[i] = C(n, i) * (i - 2 >= 0 ? pw(i, i - 2) : 1) % mod;
        f[i] = (f[i - 1] + f[i]) % mod;
    }
}

int main() {
    int t; scanf("%d%d%d", &n, &t, &mod);
    init(n);
    while(t --) {
        int l, r; scanf("%d%d", &l, &r);
        if(l == 0 && r == 0) puts("0");
        else {
            l = max(l, 1);
            ll ans = (f[r] - f[l - 1]) % mod;
            printf("%lld\n", (ans + mod) % mod);
        }
    }
}
