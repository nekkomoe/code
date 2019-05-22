#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 998244353;
const int g[2] = { 3, (mod + 1) / 3 };

ll f[N], h[N], fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}

ll F[N * 10], a[N * 10], b[N * 10], S[N];
void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) F[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = F[k], v = F[k + i / 2] * w % mod;
                F[k] = (u + v) % mod;
                F[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = F[i];
        if(ty) a[i] = a[i] * inv % mod;
    }
}

// 1,0,1,1,8,26
void geth(int l, int r) {
    if(l > r) {
        return ;
    } else if(l == r) {
        if(l == 0) {
            h[l] = 1;
            S[l] = h[l];
        } else {
            h[l] = (S[l - 1] - h[l]) % mod;
            h[l] = h[l] * fac[l - 1] % mod;
            S[l] = (S[l - 1] + h[l] * invfac[l] % mod) % mod;
        }
    } else {
        int mid = (l + r) >> 1;
        geth(l, mid);

        if(r - l < l) {
            int ta = 0, tb = 0;
            for(int i = 0 ; i <= r - l ; ++ i) {
                a[ta ++] = h[i] * invfac[i] % mod;
            }
            for(int i = l ; i <= mid ; ++ i) {
                b[tb ++] = h[i] * invfac[i] % mod;
            }
            int lim = 1; while(lim <= 4 * max(ta, tb)) lim <<= 1;
            for(int i = ta ; i < lim ; ++ i) {
                a[i] = 0;
            }
            for(int i = tb ; i < lim ; ++ i) {
                b[i] = 0;
            }
            ntt(a, 0, lim), ntt(b, 0, lim);
            for(int i = 0 ; i < lim ; ++ i) {
                a[i] = a[i] * b[i] % mod;
            }
            ntt(a, 1, lim);
            for(int i = 0 ; i < lim ; ++ i) {
                int j = l + i + 1;
                if(mid + 1 <= j && j <= r) {
                    h[j] = (h[j] + 2 * a[i] % mod) % mod;
                }
            }
        }

        int ta = 0, lim = 1;
        for(int i = l ; i <= mid ; ++ i) {
            a[ta ++] = h[i] * invfac[i] % mod;
        }
        while(lim <= 4 * ta) lim <<= 1;
        for(int i = ta ; i < lim ; ++ i) {
            a[i] = 0;
        }
        ntt(a, 0, lim);
        for(int i = 0 ; i < lim ; ++ i) {
            a[i] = a[i] * a[i] % mod;
        }
        ntt(a, 1, lim);

        for(int i = 0 ; i < lim ; ++ i) {
            int j = l + l + i + 1;
            if(mid + 1 <= j && j <= r) {
                h[j] = (h[j] + a[i]) % mod;
            }
        }

        geth(mid + 1, r);
    }
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
    geth(0, n);
    // h[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        // for(int j = 1 ; j <= i ; ++ j) {
        //     h[i] += C(i - 1, j - 1) * (fac[j - 1] - h[j - 1]) % mod * h[i - j] % mod;
        //     h[i] %= mod;
        // }
        f[i] = (fac[i - 1] - h[i - 1]) % mod;
        f[i] = f[i] * invfac[i - 1] % mod;
        if(f[i] < 0) f[i] += mod;
    }

    // puts("");
    // for(int i = 0 ; i <= 10 ; ++ i) {
    //     h[i] = (h[i] % mod + mod) % mod;
    //     printf("h[%d] = %lld\n", i, h[i]);
    // }
    // puts("");
}

int main() {
    // a[0] = a[1] = a[2] = 1;
    // ntt(a, 0, 16);
    // for(int i = 0 ; i < 16 ; ++ i) a[i] = a[i] * a[i] % mod;
    // ntt(a, 1, 16);
    // for(int i = 0 ; i < 16 ; ++ i) {
    //     printf("%lld\n", (a[i] + mod) % mod);
    // }
    // return 0;

    init(1e5);
    int t; scanf("%d", &t);
    while(t --) {
        int n; scanf("%d", &n);
        printf("%lld\n", f[n]);
    }
}
