#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define FILENAME "set"

const int mod = 998244353, N = 1e7 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
ll n, k, A;

// 可能会卡内存，记得改成int
int und[N]; // n的下降幂
int fac[N]; // k!
int invfac[N]; // 1/(k!)

ll f[N];
ll inv_1_minus_A, A_n_plus_1, A_n, trueA;

ll get_n(int k) {
    // return n < k ? 0 : (ll) fac[n] * invfac[k] % mod * invfac[n - k] % mod;
    // cout << k << ' ' << und[k] << ' ' << (ll) fac[n] * invfac[n - k] % mod << endl;
    return n < k ? 0 : (ll) und[k] * invfac[k] % mod;
}

namespace force {
    ll C(int n, int m) {
        return n < m ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    }
    void sol() {
        ll ans = 0, prod = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            prod = prod * A % mod;
            ans += prod * C(n - i, k - 1) % mod;
            ans %= mod;
        }
        ans = ans * pw(C(n, k), mod - 2) % mod;
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}

ll C(int n, int m) {
    return n < m ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

void sohowtogetf(int lim) {
    if(A == 1) {
        f[0] = (n + 1) % mod;
    } else {
        f[0] = (pw(A, n + 1) - 1) * pw(A - 1, mod - 2) % mod;
    }
    for(int k = 1 ; k <= lim ; ++ k) {
        f[k] = (
                A * f[k - 1] % mod
              - A_n_plus_1 * ((get_n(k - 1) + get_n(k)) % mod) % mod)
          * inv_1_minus_A % mod;
    }
}

void runprog() {
    scanf("%lld%lld%lld", &n, &k, &A);
    if(A==1){
        puts("1");

    }else
    if(n <= 1000000) {
        force :: sol();
    } else {
        trueA = A;
        A = pw(A, mod - 2);
        inv_1_minus_A = pw(1 - A, mod - 2);
        A_n_plus_1 = pw(A, n + 1);
        A_n = pw(A, n);

        und[0] = 1;
        for(int i = 1 ; i <= k ; ++ i) {
            und[i] = (ll) und[i - 1] * (n - i + 1) % mod;
        }

        sohowtogetf(k);

        ll fz = (f[k - 1] - get_n(k - 1) * pw(A, n) % mod) % mod * pw(trueA, n) % mod;

        ll ans = fz * pw(get_n(k), mod - 2) % mod;
        printf("%lld\n", (ans % mod + mod) % mod);
    }
}

void initfack() {
    int k = 1e7;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) fac[i] = (ll) fac[i - 1] * i % mod;
    invfac[k] = pw(fac[k], mod - 2);
    for(int i = k - 1 ; i ; -- i) invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
}

int main() {
    // freopen(FILENAME ".in", "r", stdin);
    // freopen(FILENAME ".out", "w", stdout);
    initfack();
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
