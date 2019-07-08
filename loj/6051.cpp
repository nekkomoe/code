#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1004535809;
// const int mod = 998244353;
const int N = 1e7 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

const ll g[2] = { 3, (mod + 1ll) / 3 };
ll f[N];

// int rev(int x, int n) {
//     int r = 0;
//     for(int i = 0 ; (1 << i) < n ; ++ i) {
//         r = (r << 1) | ((x >> i) & 1);
//     }
//     return r;
// }
// void ntt(ll *a, int ty, int n) {
//     for(int i = 0 ; i < n ; ++ i) {
//         f[rev(i, n)] = a[i] % mod;
//     }
//     for(int i = 2 ; i <= n ; i <<= 1) {
//         ll wn = pw(g[ty], (mod - 1) / i);
//         for(int j = 0 ; j < n ; j += i) {
//             ll w = 1;
//             for(int k = j ; k < j + i / 2 ; ++ k) {
//                 ll u = f[k], v = f[k + i / 2] * w % mod;
//                 f[k] = (u + v) % mod;
//                 f[k + i / 2] = (u - v) % mod;
//                 w = w * wn % mod;
//             }
//         }
//     }
//     for(int i = 0, inv = getinv(n) ; i < n ; ++ i) {
//         a[i] = f[i];
//         if(ty) {
//             a[i] = a[i] * inv % mod;
//         }
//     }
// }

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
    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) {
            a[i] = a[i] * inv % mod;
        }
    }
}

int n, a[N];
ll fac[N], invfac[N];
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

ll b[N];
ll c[N], d[N], e[N];

ll nekko() {
    for(int i = 1 ; i <= n ; ++ i) {
        b[i] = a[i] + n - i;
    }
    ll res = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        // n + max a
        res = res * fac[a[i]] % mod;
        res = res * invfac[b[i]] % mod;
    }
    
    int T = 1e6;

    // T = 100;

    int mn = a[1] - 1;

    for(int i = 1 ; i <= n ; ++ i) {
        mn = min(mn, a[i] - i);
        mn = min(mn, i - a[i]);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        c[(a[i] - i) - mn] ++;
        d[(i - a[i]) - mn] ++;
    }

    // max: 2T
    // for(int i = 0 ; i <= T * 4 ; ++ i) {
    //     for(int j = i ; j >= 0 ; -- j) {
    //         upd(e[i], c[j] * d[i - j] % mod);
    //     }
    // }

    // int len = 1 << 22;
    int len = 1;
    // while(len <= (1499998 * 2)) len <<= 1;
    len = 1 << 21;
    // 1004535809 = 479 * 2^21, g = 3，换而言之不能超过2^21……不然就gg了

    // while(len <= 4 * T) len <<= 1;

    // printf("len = %d\n", len);
    ntt(c, 0, len), ntt(d, 0, len);
    for(int i = 0 ; i < len ; ++ i) {
        e[i] = c[i] * d[i] % mod;
    }
    ntt(e, 1, len);

    // for(int i = 0 ; i <= 4 * T ; ++ i) {
    //     e[i] = (e[i] % mod + mod) % mod;
    //     if(e[i] > 0) {
    //         printf("%lld\n", e[i]);
    //     }
    // }


    // 这里感觉要出事啊。。。应该模phip？。。。
    for(int i = 0 ; i < len ; ++ i) {
        ll val = i + 2 * mn;
        if(val >= 1) {
            res = res * pw(val, (e[i] % mod + mod) % mod) % mod;
        }
    }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int j = i + 1 ; j <= n ; ++ j) {
    //         res = res * (b[i] - b[j]) % mod;
    //     }
    // }

    return res;
}

int main() {

    // printf("%lld\n", 3 * 334845270 % mod);

    // c[0] = c[1] = c[2] = 1;
    // ntt(c, 0, 16);
    // for(int i = 0 ; i < 16 ; ++ i) {
    //     c[i] = c[i] * c[i] % mod;
    // }
    // ntt(c, 1, 16);
    // for(int i = 0 ; i < 16 ; ++ i) {
    //     printf("%lld\n", (c[i] % mod + mod) % mod);
    // }

    init(N - 1);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    ll ans = nekko();
    printf("%lld\n", (ans % mod + mod) % mod);
}
