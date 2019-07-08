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

const int g[2] = { 3, (mod + 1) / 3 };
const int N = 1ll << 24;

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

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace NEKKO {
ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

char str[N];
int cnt[N], n;
ll f[N], fac[N], invfac[N];
ll g[N], h[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i >= 1 ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

int main() {

    init(N - 1);

    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        cnt[i] = cnt[i - 1] + (str[i] == '>');
    }
    for(int i = 0 ; i <= n ; ++ i) {
        g[i] = cnt[i] & 1 ? -1 : 1;
        h[i] = str[i] != '<' ? g[i] : 0;
    }
    ++ n;

    function<void(int,int)> sol = [&] (int l, int r) {
        int mid = (l + r) >> 1;
        if(l == r) {
            if(l == 0) {
                f[0] = 1;
            } else {
                (f[l] *= g[l - 1]) %= mod;
            }
        } else {
            sol(l, mid);

            // [l, mid] -> [mid + 1, r]
            vector<ll> a, b, c;

            for(int i = l ; i <= mid ; ++ i) {
                a.push_back(f[i] * h[i] % mod);
            }
            for(int i = 0 ; i <= r - l + 10 ; ++ i) {
                b.push_back(invfac[i + 1]);
            }

            NTT :: mul(a, b, c);
            for(int i = 0 ; i < c.size() ; ++ i) {
                int tar = l + i + 1;
                if(mid + 1 <= tar && tar <= r) {
                    upd(f[tar], c[i]);
                }
            }

            sol(mid + 1, r);
        }
    };

    if(0) {
        f[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 0 ; j < i ; ++ j) {
                upd(f[i], h[j] * f[j] * invfac[i - j] % mod);
            }
            (f[i] *= g[i - 1]) %= mod;
        }
    } else {
        sol(0, n);
    }

    // vector<ll> G(n + 10);
    // for(int i = 0 ; i <= n ; ++ i) {
    //     G[i] = i - 1 >= 0 ? 1 : G[i - 1];
    // }
    // vector<ll> T(n + 10);
    // for(int i = 0 ; i <= n ; ++ i) {
    //     T[i] = invfac[i + 1];
    // }
    
    // vector<ll> GH(n + 10);
    // for(int i = 0 ; i <= n ; ++ i) {
    //     GH[i] = G[i] * getinv(h[i]) % mod;
    // }

    // vector<ll> GT;
    // NTT :: mul(GH, T, GT);
    // reverse(GT.begin(), GT.end()), GT.push_back(0), reverse(GT.begin(), GT.end()); // GT.push_front(0);
    // GT[0] ++;
    // f[n] = F[n] * G[n] % mod;

    ll ans = f[n] * fac[n] % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
    return 0;
}


// int main() {
//     int n; scanf("%d", &n);
//     vector<ll> a, res;
//     for(int i = 0 ; i < n ; ++ i) {
//         int x; scanf("%d", &x);
//         a.push_back(x);
//     }
//     GET_INV :: get_inv(a, res, n);
//     for(int i = 0 ; i < n ; ++ i) {
//         printf("%lld ", (res[i] % mod + mod) % mod);
//     }
// }

}

int main() {
    NEKKO :: main();
}
