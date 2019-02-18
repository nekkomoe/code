#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native") 
#pragma GCC optimize("inline", "fast-math", "unroll-loops", "no-stack-protector")
#pragma GCC optimize("unroll-all-loops")
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, M = 20, mod = 998244353, g[2] = { 3, (mod + 1) / 3 };
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n, m;
ll fac[N], invfac[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll S[M][M];

ll h[N];

const int p = mod;
ll inv(ll a) {
    return pw(a, p - 2);
}
    
namespace NTT {
    const int N = 263000, p = mod;
    ll f[N];
    int rev(int x, int n) {
        int r = 0;
        for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
        return r;
    }
    void ntt(ll *a, int n, int ty) {
        for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
        for(int i = 2 ; i <= n ; i <<= 1) {
            ll wn = pw(g[ty], (p - 1) / i);
            for(int j = 0 ; j < n ; j += i) {
                ll w = 1;
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = f[k], v = w * f[k + i / 2] % p;
                    f[k] = (u + v) % p, f[k + i / 2] = ((u - v) % p + p) % p;
                    w = w * wn % p;
                }
            }
        }
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i];
            if(ty == 1) a[i] = a[i] * inv(n) % p;
        }
    }
    
}

namespace GETINV {
    const int p = mod;
    ll aa[N], t[N], a[N], b[N], h[N];
    void sol(int n) {
        if(n == 1) {
            b[0] = inv(a[0]);
        } else {
            sol((n + 1) / 2);
            int len = 1; while(len <= 2 * n - 2) len <<= 1;
            for(int i = 0 ; i < n ; ++ i) aa[i] = a[i], t[i] = 2 * b[i] % p;
            NTT :: ntt(aa, len, 0), NTT :: ntt(b, len, 0);
            for(int i = 0 ; i < len ; ++ i) h[i] = aa[i] * b[i] % p * b[i] % p;
            NTT :: ntt(h, len, 1);
            for(int i = 0 ; i < n ; ++ i) b[i] = ((t[i] - h[i]) % p + p) % p;
            for(int i = n ; i < len ; ++ i) b[i] = 0;
        }
    }
}

namespace bzoj3456 {
    const int N = 263000, p = mod;
    
    ll F[N], G[N], T[N], Ginv[N];
    void runprog() {
        for(int i = 1 ; i <= n ; ++ i) T[i] = pw(2, (ll) i * (i - 1) / 2) * inv(fac[i - 1]) % p;
        for(int i = 0 ; i <= n ; ++ i) G[i] = pw(2, (ll) i * (i - 1) / 2) * inv(fac[i]) % p, GETINV :: a[i] = G[i];
        GETINV :: sol(n + 10);
        for(int i = 0 ; i <= n ; ++ i) Ginv[i] = GETINV :: b[i];
        int len = 1; while(len <= 2 * n + 10) len <<= 1;
        NTT :: ntt(Ginv, len, 0), NTT :: ntt(T, len, 0);
        for(int i = 0 ; i < len ; ++ i) F[i] = Ginv[i] * T[i] % p;
        NTT :: ntt(F, len, 1);
        :: h[0] = 0;
        for(int n = 1 ; n <= :: n ; ++ n) {
            :: h[n] = F[n] * fac[n - 1] % p;
        }
    }
}

namespace getH {
    void runprog() {
        bzoj3456 :: runprog();
    }
}

ll f[M][N];

ll F[N], G[N], H[N];
ll up[N], dn[N];
ll A[N], B[N];

void mul(ll *a, ll *b, ll *tar, int len, int n) {
    for(int i = 0 ; i < len ; ++ i) {
        tar[i] = A[i] = B[i] = 0;
    }

    // for(int i = 0 ; i < len ; ++ i) {
    //     for(int j = 0 ; j + i < len ; ++ j) {
    //         (tar[i + j] += a[i] * b[j] % mod) %= mod;
    //     }
    // }
    // return ;

    for(int i = 0 ; i <= n ; ++ i) {
        A[i] = a[i], B[i] = b[i];
    }
    NTT :: ntt(A, len, 0), NTT :: ntt(B, len, 0);
    for(int i = 0 ; i < len ; ++ i) {
        A[i] = A[i] * B[i] % mod;
    }
    NTT :: ntt(A, len, 1);
    for(int i = 0 ; i < len ; ++ i) {
        tar[i] = A[i];
    }
}

void getinv(ll *src, ll *tar, int n, int len) {
    // ll aa[N], t[N], a[N], b[N], h[N];
    memset(GETINV :: aa, 0, sizeof GETINV :: aa);
    memset(GETINV :: t, 0, sizeof GETINV :: t);
    memset(GETINV :: a, 0, sizeof GETINV :: a);
    memset(GETINV :: b, 0, sizeof GETINV :: b);
    memset(GETINV :: h, 0, sizeof GETINV :: h);
    for(int i = 0 ; i <= n ; ++ i) {
        GETINV :: a[i] = src[i];
    }
    GETINV :: sol(n + 5);
    for(int i = 0 ; i <= n ; ++ i) {
        tar[i] = GETINV :: b[i];
    }
}

ll GH[N], X[N], Y[N];

void cdq(ll *tar, int l, int r) {
    if(l == r) {
        (tar[l] += GH[l]) %= mod;
        if(l) tar[l] = tar[l] * fac[l - 1] % mod;
    } else {
        int mid = (l + r) >> 1;
        cdq(tar, l, mid);
        int len = 1; while(len <= 2 * (r - l + 1)) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) X[i] = Y[i] = 0;
        for(int i = l ; i <= mid ; ++ i) X[i - l] = tar[i] * invfac[i] % mod;
        for(int i = 0 ; i <= r - l ; ++ i) Y[i] = H[i];
        NTT :: ntt(X, len, 0), NTT :: ntt(Y, len, 0);
        for(int i = 0 ; i < len ; ++ i) X[i] = X[i] * Y[i] % mod;
        NTT :: ntt(X, len, 1);
        for(int i = mid + 1 ; i <= r ; ++ i) (tar[i] += X[i - l]) %= mod;
        cdq(tar, mid + 1, r);
    }
}

namespace getF {
    void runprog() {
        for(int n = 0 ; n <= :: n ; ++ n) f[0][n] = pw(2, C(n, 2));
        int len = 1; while(len <= 2 * n) len <<= 1;
        H[0] = 0;
        for(int i = 1 ; i <= n ; ++ i) H[i] = h[i] * invfac[i - 1] % mod;
        for(int k = 1 ; k <= m ; ++ k) {
            for(int i = 0 ; i <= n ; ++ i) G[i] = f[k - 1][i] * invfac[i] % mod;
            mul(G, H, GH, len, n);
            cdq(f[k], 0, n);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    init(int(1e6));
    S[0][0] = 1;
    for(int i = 1 ; i <= m ; ++ i)
        for(int j = 1 ; j <= i ; ++ j)
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % mod) % mod;
    getH :: runprog();
    getF :: runprog();

    ll ans = 0;
    for(int k = 1 ; k <= m ; ++ k) {
        ans = (ans + S[m][k] * f[k][n] % mod * fac[k] % mod) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}
