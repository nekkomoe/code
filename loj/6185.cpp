#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n;
ll f[410], fac[410];
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
ll C(ll n, ll m) {
    if(n < m || m < 0) {
        return 0;
    } else if(m == 3) {
        return n * (n - 1) % mod * (n - 2) % mod * pw(6, mod - 2) % mod;
    } else if(m == 2) {
        return n * (n - 1) % mod * pw(2, mod - 2) % mod;
    } else if(m == 1) {
        return n;
    } else {
        assert(0);
        return 0;
    }
}

int main() {
    scanf("%d", &n);
    fac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    f[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int a = 0 ; a <= i - 1 ; ++ a) {
            for(int b = a ; a + b <= i - 1 ; ++ b) {
                int c = i - 1 - a - b;
                if(c >= b) {
                    if(a == c) {
                        // a = b = c
                        upd(f[i], C(f[a] + 3 - 1, 3));
                    } else if(a == b) {
                        // a = b < c
                        upd(f[i], C(f[a] + 2 - 1, 2) * f[c] % mod);
                    } else if(b == c) {
                        // a < b = c
                        upd(f[i], f[a] * C(f[b] + 2 - 1, 2) % mod);
                    } else {
                        // a < b < c
                        upd(f[i], f[a] * f[b] % mod * f[c] % mod);
                    }
                }
            }
        }
    }
    printf("%lld\n", f[n]);
}
