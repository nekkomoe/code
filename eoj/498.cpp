// luogu-judger-enable-o2
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

const int g[2] = { 3, pw(g[0], mod - 2) };
const int N = 1ll << 25;

namespace NTT {
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

/*
// NTT with vector
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
*/

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

namespace GET_POW_LOG2 {
    void get_pow_log2(vector<ll> &inp, ll k, vector<ll> &res) {
        int n = inp.size();
        res.resize(1), res[0] = 1;
        for( ; k ; k >>= 1, NTT :: mul(inp, inp, inp), inp.resize(n)) {
            if(k & 1) {
                NTT :: mul(res, inp, res);
                res.resize(n);
            }
        }
    }
}

namespace GET_POW_EXPLN {
    void get_pow_expln(vector<ll> &inp, ll k, vector<ll> &res) {
        int n = inp.size();
        GET_LN :: get_ln(inp, inp);
        for(int i = 0 ; i < inp.size() ; ++ i) inp[i] = inp[i] * k % mod;
        GET_EXP :: get_exp(inp, res);
        res.resize(n);
    }
}

namespace GET_MINUS {
    void get_minus(vector<ll> &a, vector<ll> &b, vector<ll> &res) {
        res = a;
        if(b.size() > a.size()) res.resize(b.size());
        for(int i = 0 ; i < b.size() ; ++ i) res[i] = (res[i] - b[i]) % mod;
    }
}

namespace GET_DIVISION {

    void to_rev(vector<ll> &f, vector<ll> &res) {
        res = f;
        reverse(res.begin(), res.end());
    }

    void get_division(vector<ll> &f, vector<ll> &g, vector<ll> &h, vector<ll> &r) {
        // f = g * h + r
        int n = f.size(), m = g.size();
        vector<ll> f_rev, g_rev, h_rev;
        to_rev(f, f_rev), to_rev(g, g_rev);
        if(g_rev.size() < n - m + 1) g_rev.resize(n - m + 1);
        GET_INV :: get_inv(g_rev, g_rev, n - m + 1);
        NTT :: mul(f_rev, g_rev, h_rev);
        h_rev.resize(n - m + 1);
        to_rev(h_rev, h);
        vector<ll> gh;
        NTT :: mul(g, h, gh);
        GET_MINUS :: get_minus(f, gh, r);
        r.resize(m);
    }
}

// TLE
namespace GET_PTS_VAL {
    vector<ll> f, pts, res;

    vector<vector<ll> > mem;
    vector<pair<int, int> > ch;
    int pos;

    void sol_F(int l, int r, vector<ll> f) {
        // f.resize(r - l + 2);
        int id = pos ++;
        if(l == r) {
            res[l] = f[0];
        } else {
            int mid = (l + r) >> 1;
            vector<ll> h, res;
            GET_DIVISION :: get_division(f, mem[ch[id].first], h, res);
            sol_F(l, mid, res);
            GET_DIVISION :: get_division(f, mem[ch[id].second], h, res);
            sol_F(mid + 1, r, res);
        }
    }

    int sol_X(int l, int r) {
        vector<ll> X;
        int lc = 0, rc = 0;
        int id = pos ++;
        mem.push_back(X), ch.push_back(make_pair(lc, rc));
        if(l == r) {
            X.resize(2);
            X[0] = -pts[l];
            X[1] = 1;
        } else {
            int mid = (l + r) >> 1;
            lc = sol_X(l, mid), rc = sol_X(mid + 1, r);
            NTT :: mul(mem[lc], mem[rc], X);
        }
        X.resize(r - l + 2);
        mem[id] = X;
        ch[id] = make_pair(lc, rc);
        return id;
    }

    void get_pts_val(vector<ll> &inp_f, vector<ll> &inp_pts, vector<ll> &tar_res) {
        // assert(f.size() == pts.size())
        mem.clear(), ch.clear();
        f = inp_f, pts = inp_pts;
        if(f.size() < pts.size()) f.resize(pts.size());
        else pts.resize(f.size());
        int n = f.size();
        res.resize(n);
        pos = 0, sol_X(0, n - 1);
        pos = 0, sol_F(0, n - 1, f);
        tar_res = res;
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m), ++ n;
    vector<ll> f, pts, ans;
    for(int i = 0, x ; i < n ; ++ i) {
        scanf("%d", &x);
        f.push_back(x);
    }
    for(int i = 0, x ; i < m ; ++ i) {
        scanf("%d", &x);
        pts.push_back(x);
    }
    GET_PTS_VAL :: get_pts_val(f, pts, ans);
    for(int i = 0 ; i < m ; ++ i) {
        printf("%lld\n", (ans[i] % mod + mod) % mod);
    }
}
