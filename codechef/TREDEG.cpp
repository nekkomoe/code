#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 };
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, k, lim;

ll f[N], a[N], res[N], fac[N], invfac[N];

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}

void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) {
        f[rev(i, n)] = a[i];
    }
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = f[k + i / 2] * w % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    if(ty) {
        for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
            a[i] = f[i] * inv % mod;
        }
    } else {
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i];
        }
    }
}

ll A[N], B[N];

void mul(ll *a, ll *b) {

    // printf("lim = %d\n", lim);
    // puts("before: ");
    // for(int i = 0 ; i < lim ; ++ i) {
    //     printf("%lld, ", (a[i] + mod) % mod);
    // } puts("");
    // for(int i = 0 ; i < lim ; ++ i) {
    //     printf("%lld, ", (b[i] + mod) % mod);
    // } puts("");

    for(int i = 0 ; i < lim ; ++ i) {
        A[i] = a[i], B[i] = b[i];
    }
    ntt(A, 0, lim), ntt(B, 0, lim);
    for(int i = 0 ; i < lim ; ++ i) {
        A[i] = A[i] * B[i] % mod;
    }
    ntt(A, 1, lim);
    for(int i = 0 ; i <= n ; ++ i) {
        a[i] = A[i];
    }

    // puts("after: ");
    // for(int i = 0 ; i < lim ; ++ i) {
    //     printf("%lld, ", (a[i] + mod) % mod);
    // } puts("");
}

void pw(ll T) {
    res[0] = 1;
    for( ; T ; T >>= 1) {
        if(T & 1) {
            mul(res, a);
        }
        mul(a, a);
    }
}

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll calc(ll m) {
    ll res = 0, prod = 1;
    for(int i = 0 ; i <= m ; ++ i) {
        int j = m - i;
        ll val = prod * invfac[i] % mod * C(n, j) % mod;
        prod = prod * n % mod;
        res = (res + val) % mod;
    }
    return res;
}

void runprog() {
    scanf("%d%d", &n, &k);
    if(n == 1) {
        puts("1");
    } else if(k == 1) {
        ll inv = pw(pw(n, n - 2), mod - 2);
        printf("%lld\n", fac[n - 2] * calc(n - 2) % mod * inv % mod);
    } else {
        lim = 1; while(lim <= 2 * n) lim <<= 1;
        for(int i = 0 ; i < lim ; ++ i) {
            a[i] = res[i] = 0;
        }
        for(int i = 0 ; i <= n ; ++ i) {
            a[i] = pw(i + 1, k) * invfac[i] % mod;
        }
        pw(n);
        ll inv = pw(pw(n, n - 2), mod - 2);
        printf("%lld\n", (fac[n - 2] * res[n - 2] % mod * inv % mod + mod) % mod);
    }
}

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

int main() {

    // for(int i = 0 ; i <= 3 ; ++ i) a[i] = 1;
    // ntt(a, 0, 16);
    // for(int i = 0 ; i < 16 ; ++ i) a[i] = a[i] * a[i] % mod;
    // ntt(a, 1, 16);
    // for(int i = 0 ; i < 16 ; ++ i) {
    //     printf("%lld, ", (a[i] + mod) % mod);
    // } puts("");

    init(N - 1);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
