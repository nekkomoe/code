#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 950009857;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

const int g[2] = { 7, pw(g[0], mod - 2) };

namespace NTT {
    int rev(int x, int n) {
        int r = 0;
        for(int i = 0 ; (1 << i) < n ; ++ i) {
            r = (r << 1)|  ((x >> i) & 1);
        }
        return r;
    }
    vector<ll> f, A, B, C;
    void ntt(vector<ll> &a, int ty, int n) {
        f.resize(n);
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
        A = a, B = b;
        A.resize(len), B.resize(len);
        ntt(A, 0, len), ntt(B, 0, len);
        for(int i = 0 ; i < len ; ++ i) A[i] = A[i] * B[i] % mod;
        ntt(A, 1, len);
        res.resize(n + m);
        for(int i = 0 ; i < n + m ; ++ i) res[i] = A[i];
    }
    void mul3(vector<ll> &a, vector<ll> &b, vector<ll> &c, vector<ll> &res) {
        int n = a.size(), m = b.size(), o = c.size();
        int len = 1; while(len <= 2 * (n + m + o)) len <<= 1;
        A = a, B = b, C = c;
        A.resize(len), B.resize(len), C.resize(len);
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

namespace GET_INTEGRAL {
    void get_integral(vector<ll> &inp, vector<ll> &res) {
        int n = inp.size();
        res.resize(n + 1);
        res[0] = 0;
        // ax^n -> a/(n+1)x^{n+1}
        for(int i = 1 ; i < n + 1 ; ++ i) {
            res[i] = inp[i - 1] * pw(i, mod - 2) % mod;
        }
    }
}

namespace GET_DIFFERENTIATION {
    void get_differentiation(vector<ll> &inp, vector<ll> &res) {
        int n = inp.size();
        res.resize(n - 1);
        // ax^n -> anx^{n-1}
        for(int i = 0 ; i < n - 1 ; ++ i) {
            res[i] = inp[i + 1] * (i + 1) % mod;
        }
    }
}

namespace GET_LN {
    void get_ln(vector<ll> &inp, vector<ll> &res) {
        int n = inp.size();
        vector<ll> f, f_diff, f_inv; f = inp;
        GET_DIFFERENTIATION :: get_differentiation(f, f_diff);
        GET_INV :: get_inv(f, f_inv, n);
        NTT :: mul(f_diff, f_inv, f);
        GET_INTEGRAL :: get_integral(f, res);
    }
}

namespace GET_EXP {
    vector<ll> f, a;
    void sol(int n) {
        if(n == 1) {
            // assert(a[0] == 1);
            f.resize(1), f[0] = 1;
        } else {
            sol((n + 1) / 2);
            vector<ll> g, res;
            f.resize(n);
            GET_LN :: get_ln(f, g);
            for(int i = 0 ; i < g.size() ; ++ i) g[i] = -g[i];
            for(int i = 0 ; i < n ; ++ i) g[i] = (g[i] + a[i]) % mod;
            g[0] ++;
            NTT :: mul(g, f, res);
            res.resize(n);
            f = res;
        }
    }

    void get_exp(vector<ll> &inp, vector<ll> &res) {
        int n = inp.size();
        a = inp;
        sol(n);
        res.resize(n);
        for(int i = 0 ; i < n ; ++ i) {
            res[i] = f[i];
        }
    }
}

const int INPN = 1e5 + 10;
ll fac[INPN], invfac[INPN];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

void divd(vector<ll> &g, vector<ll> &res) {
    int n = g.size();
    res.resize(n - 1);
    for(int i = n - 2 ; i >= 0 ; -- i) {
        res[i] = g[i + 1];
    }
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    vector<ll> f(n + 1), g(n + 1);
    init(n);
    for(int i = 1 ; i <= k ; ++ i) {
        int x; scanf("%d", &x);
        g[x] = 1;
    }
    vector<ll> res;
    divd(g, res), g = res;
    GET_INTEGRAL :: get_integral(g, res), g = res;
    GET_EXP :: get_exp(g, res), g = res;
    for(int i = 1 ; i <= n ; ++ i) {
        g[i] = g[i] * fac[i] % mod;
        printf("%lld\n", (g[i] % mod + mod) % mod);
    }
}
