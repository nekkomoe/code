#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6 + 10, mod = 1e9 + 7;

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
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int n, k;
ll f[2010][2010];
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

int main() {
    init(N - 1);
    scanf("%d%d", &n, &k);
    if(! -- k) {
        puts("1");
    } else {
        f[0][0] = 1;
        for(int i = 0 ; i <= n ; ++ i) {
            for(int j = i ; j <= n ; ++ j) {
                if(j) {
                    if(i - 1 >= 0) {
                        upd(f[i][j], f[i - 1][j]);
                    }
                    upd(f[i][j], f[i][j - 1] * C(i + (j - 1) * k + k - 1, k - 1) % mod);
                }
            }
        }
        printf("%lld\n", f[n][n] * fac[n] % mod);
    }
}
