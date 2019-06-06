#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 }, N = 3e6 + 10;

ll f[N], p[N], q[N], S[N], A[N], fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
void ntt(ll *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    if(ty) {
        int inv = pw(n, mod - 2);
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i] * inv % mod;
        }
    } else {
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i];
        }
    }
}

void mul(int n) {
    ntt(p, n, 0), ntt(q, n, 0);
    for(int i = 0 ; i < n ; ++ i) p[i] = p[i] * q[i] % mod;
    ntt(p, n, 1);
}

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

void sol(int n) {
    if(n == 1) {
        S[1] = 1;
    } else if(n & 1) {
        sol(n - 1);
        for(int i = n ; i >= 0 ; -- i) {
            if(i) S[i] = (S[i - 1] + S[i] * (n - 1) % mod) % mod;
        }
    } else {
        sol(n / 2); int lef = n / 2;
        int len = 1; while(len < 4 * n) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) p[i] = q[i] = 0;
        for(int i = 0 ; i <= lef ; ++ i) {
            p[i] = S[i] * fac[i] % mod;
            q[lef - i] = pw(lef, i) * invfac[i] % mod;
        }
        mul(len);
        for(int i = 0 ; i <= lef ; ++ i) p[i] = p[i + lef] * invfac[i] % mod;
        for(int i = lef + 1 ; i < len ; ++ i) p[i] = 0;
        for(int i = 0 ; i < len ; ++ i) q[i] = 0;
        for(int i = 0 ; i <= lef ; ++ i) q[i] = S[i];
        mul(len);
        for(int i = 0 ; i <= n ; ++ i) S[i] = p[i];
    }
}

int main() {

    // ll f[N], p[N], q[N], S[N], A[N], fac[N], invfac[N];
    // memset(f, 0, sizeof f);
    // memset(p, 0, sizeof p);
    // memset(q, 0, sizeof q);
    // memset(S, 0, sizeof S);
    // memset(A, 0, sizeof A);
    // memset(fac, 0, sizeof fac);
    // memset(invfac, 0, sizeof invfac);


    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    if(!a || !b || a + b - 2 > n - 1) return puts("0"), 0;
    if(n == 1) return puts("1"), 0;
    init(N - 10);
    sol(n - 1);
    ll ans = S[a + b - 2] * C(a + b - 2, a - 1) % mod;
    printf("%lld\n", (ans + mod) % mod);
}
