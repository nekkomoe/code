#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 924844033, N = 2010;

ll pw(ll a, ll b) {
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

int n, k, a[N * 2], m;
ll f[N * 2][N * 2][2];
ll fac[N * 2];

void init(int n) {
    fac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
}

int main() {
    init(N * 2 - 1);
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= k ; ++ i) {
        for(int p = 1 ; p <= 2 ; ++ p) {
            for(int j = i ; j <= n ; j += k) {
                a[++ m] = i != j;
            }
        }
    }
    f[0][0][0] = 1;
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % mod;
            if(a[i] && j >= 1) {
                f[i][j][1] = f[i - 1][j - 1][0];
            }
        }
    }

    ll ans = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        upd(ans, (i & 1 ? -1 : 1) * (f[2 * n][i][0] + f[2 * n][i][1]) % mod * fac[n - i] % mod);
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
