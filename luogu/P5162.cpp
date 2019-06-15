// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 1e5 + 10;


ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

namespace NTT {
    const int g[2] = { 3, pw(g[0], mod - 2) };
    const int N = 1ll << 24;

    int rev(int x, int n) {
        int r = 0;
        for(int i = 0 ; (1 << i) < n ; ++ i) {
            r = (r << 1)|  ((x >> i) & 1);
        }
        return r;
    }
    ll f[N], A[N], B[N], C[N];
    void ntt(ll *a, int ty, int n) {
        for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];

        for(int i = 2 ; i <= n ; i <<= 1) {
            ll wn = pw(g[ty], (mod - 1) / i);
            for(int j = 0 ; j < n ; j += i) {
                ll w = 1;
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = f[k], v = w * f[k + i / 2] % mod;
                    f[k] = (u + v) % mod, f[k + i / 2] = (u - v) % mod;
                    w = w * wn % mod;
                }
            }
        }

        for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
            a[i] = f[i];
            if(ty) {
                a[i] = a[i] * inv % mod;
            }
        }
    }
    void mul(vector<ll> &a, vector<ll> &b, vector<ll> &res) {
        int n = a.size(), m = b.size();
        int len = 1; while(len <= 2 * (n + m)) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) A[i] = B[i] = 0;
        for(int i = 0 ; i < n ; ++ i) A[i] = a[i];
        for(int i = 0 ; i < m ; ++ i) B[i] = b[i];
        ntt(A, 0, len), ntt(B, 0, len);
        for(int i = 0 ; i < len ; ++ i) A[i] = A[i] * B[i] % mod;
        ntt(A, 1, len);
        res.resize(n + m);
        for(int i = 0 ; i < n + m ; ++ i) res[i] = A[i];
    }
    void mul3(vector<ll> &a, vector<ll> &b, vector<ll> &c, vector<ll> &res) {
        int n = a.size(), m = b.size(), o = c.size();
        int len = 1; while(len <= 2 * (n + m + o)) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) A[i] = B[i] = C[i] = 0;
        for(int i = 0 ; i < n ; ++ i) A[i] = a[i];
        for(int i = 0 ; i < m ; ++ i) B[i] = b[i];
        for(int i = 0 ; i < o ; ++ i) C[i] = c[i];
        ntt(A, 0, len), ntt(B, 0, len), ntt(C, 0, len);
        for(int i = 0 ; i < len ; ++ i) A[i] = A[i] * B[i] % mod * C[i] % mod;
        ntt(A, 1, len);
        res.resize(n + m + o);
        for(int i = 0 ; i < n + m + o ; ++ i) res[i] = A[i];
    }
}

namespace GET_INV {

    vector<ll> a, f, g;

    void sol(int n) {
        if(n == 1) {
            f.resize(1);
            f[0] = pw(a[0], mod - 2);
        } else {
            sol((n + 1) / 2);
            g.resize(n);
            for(int i = 0 ; i < n ; ++ i) g[i] = 0;
            for(int i = 0 ; i < f.size() ; ++ i) g[i] = 2 * f[i] % mod;
            vector<ll> A(n); for(int i = 0 ; i < n ; ++ i) A[i] = a[i];
            vector<ll> res; NTT :: mul3(A, f, f, res);
            for(int i = 0 ; i < n ; ++ i) g[i] = (g[i] - res[i]) % mod;
            f = g;
        }
    }

    void get_inv(vector<ll> &inp, vector<ll> &res, int n) {
        if(n == 0) {
            res.resize(1), res[0] = 0;
        } else {
            a = inp;
            sol(n);
            res.resize(n);
            for(int i = 0 ; i < n ; ++ i) res[i] = f[i];
        }
    }
}


ll getinv(ll n) {
    return pw(n, mod - 2);
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

void upd(ll &x, ll y) {
    x = (x + y) % mod;
}
ll f[N], g[N], ans[N];
void build(int n) {
    // f[0] = 1;
    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j <= i ; ++ j) {
    //         upd(f[i], C(i, j) * f[i - j] % mod);
    //     }
    // }

    vector<ll> a(n + 10), res;
    a[0] = 1;
    for(int i = 1 ; i < n + 10 ; ++ i) {
        a[i] = -invfac[i];
    }
    GET_INV :: get_inv(a, res, n + 10);
    for(int i = 0 ; i <= n ; ++ i) {
        f[i] = (res[i] + mod) % mod * fac[i] % mod;
    }

    vector<ll> b(n + 10);
    for(int i = 0 ; i <= n ; ++ i) {
        b[i] = f[i] * invfac[i] % mod;
    }
    auto bb = b;
    -- bb[0];
    NTT :: mul(b, bb, res);

    for(int i = 1 ; i <= n ; ++ i) {
        // for(int j = 1 ; j <= i ; ++ j) {
        //     upd(g[i], C(i, j) * (f[i - j] + g[i - j]) % mod);
        // }
        g[i] = res[i] * fac[i] % mod;
    }

    // for(int i = 1 ; i <= 5 ; ++ i) {
    //     printf("%lld\n", g[i] % mod);
    // }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = 1 ; j <= i ; ++ j) {
    //         upd(g[i], C(i, j) * (f[i - j] + g[i - j]) % mod);
    //     }
    // }

    for(int i = 1 ; i <= n ; ++ i) {
        ans[i] = g[i] * getinv(f[i]) % mod;
    }
}

int main() {
    init(N - 1);
    build(1e5);
    int t; scanf("%d", &t);
    while(t --) {
        int n; scanf("%d", &n);
        printf("%lld\n", (ans[n] % mod + mod) % mod);
    }
}
