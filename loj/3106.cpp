// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 1e6 + 10;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
ll inv(ll x) {
    return pw(x, mod - 2);
}
ll fac[N], invfac[N];
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

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
int n, num[5];
ll f[5][2010];

ll calc(int rm) {

    int mem[5];
    for(int i = 1 ; i <= 4 ; ++ i) {
        mem[i] = num[i];
        if(num[i] - rm < 0) {
            return 0;
        }
    }

    for(int i = 1 ; i <= 4 ; ++ i) {
        num[i] -= rm;
    }
    int m = n - 4 * rm;
    f[0][0] = 1;
    for(int i = 1 ; i <= 4 ; ++ i) {
        for(int j = 0 ; j <= m ; ++ j) {
            f[i][j] = 0;
            for(int k = 0 ; k <= min(j, num[i]) ; ++ k) {
                (f[i][j] = f[i][j] + f[i - 1][j - k] * invfac[k] % mod) %= mod;
            }
        }
    }

    for(int i = 1 ; i <= 4 ; ++ i) {
        num[i] = mem[i];
    }

    return fac[m] * f[4][m] % mod;
}

int main() {
    init(N - 1);
    scanf("%d%d%d%d%d", &n, &num[1], &num[2], &num[3], &num[4]);
    ll ans = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        // printf("%lld, %lld\n", C(n - 3 * i, i), calc(i));
        ans += C(n - 3 * i, i) * (i & 1 ? -1 : 1) * calc(i) % mod;
        ans %= mod;
    }
    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
