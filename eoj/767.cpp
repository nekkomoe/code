#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
// const int N = 5010;
const int mod = 1e9 + 7;
// ll a[N][N];
int n;

// void sol() {
//     for(int i = 0 ; i < n ; ++ i) {
//         for(int j = 0 ; j < n ; ++ j) {
//             int val = ((__builtin_popcount((i | j) ^ i)) + 1) % 2;
//             a[i + 1][j + 1] = val;
//         }
//     }
// }

ll pw(ll a, ll b) {
    ll r = 1;
    a %= mod;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

// void poi() {
//     puts("No Solution");
//     exit(0);
// }

// void output() {
//     for(int i = 1 ; i <= n ; ++ i) {
//         for(int j = 1 ; j <= n ; ++ j) {
//             printf("%lld ", a[i][j]);
//         }
//         printf(" | ");
//         for(int j = n + 1 ; j <= n * 2 ; ++ j) {
//             printf("%lld ", a[i][j]);
//         }
//         puts("");
//     }
//     puts("");
// }

// void getinv() {
//     for(int i = 1 ; i <= n ; ++ i) {
//         for(int j = 1 ; j <= n ; ++ j) {
//             a[i][n + j] = 0;
//         }
//         a[i][n + i] = 1;
//     }
    
//     // output();

//     for(int i = 1 ; i <= n ; ++ i) {
//         int ch = i;
//         for(int j = i ; j <= n ; ++ j) {
//             if(a[j][i]) {
//                 ch = j;
//                 break;
//             }
//         }
//         for(int j = i ; j <= n * 2 ; ++ j) {
//             swap(a[i][j], a[ch][j]);
//         }
//         if(!a[i][i]) poi();
//         for(int j = i + 1 ; j <= n ; ++ j) {
//             ll x = a[j][i] * pw(a[i][i], mod - 2) % mod;
//             for(int k = i ; k <= n * 2 ; ++ k) {
//                 (a[j][k] -= a[i][k] * x % mod) %= mod;
//             }
//         }
//     }
    
//     for(int i = n ; i >= 1 ; -- i) {
//         if(!a[i][i]) poi();
//         for(int j = i - 1 ; j >= 1 ; -- j) {
//             ll x = a[j][i] * pw(a[i][i], mod - 2) % mod;
//             for(int k = i ; k <= n * 2 ; ++ k) {
//                 (a[j][k] -= a[i][k] * x % mod) %= mod;
//             }
//         }
//         ll x = pw(a[i][i], mod - 2);
//         for(int j = i ; j <= n * 2 ; ++ j) {
//             (a[i][j] *= x) %= mod;
//         }
//     }
// }

// ll b[N], c[N], t[N][N];

// void n2_runit() {
//     ll val = pw(n * pw(2, mod - 2) % mod, mod - 2);
//     for(int i = n ; i >= 1 ; -- i) {
//         for(int j = n ; j >= 1 ; -- j) {
//             a[i][j + n] = val * (a[n - i + 1][n - j + 1] == 1 ? 1 : -1);
//         }
//     }

//     a[1][n + n] = val - 1;
// }

namespace fwt {
    const int N = 2e6 + 10;
    ll b[N];
    void runprog() {
        for(int i = 0 ; i < n ; ++ i) {
            scanf("%lld", &b[i]);
            b[i] %= mod;
        }
        if(n == 1) {
            printf("%lld\n", b[0]);
            return ;
        }
        ll coef = b[n - 1] * pw(2, mod - 2) % mod * n % mod;
        for(int i = 2 ; i <= n ; i <<= 1) {
            for(int j = 0 ; j < n ; j += i) {
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = b[k], v = b[k + i / 2];
                    (b[k] += v) %= mod;
                    (b[k + i / 2] -= u) %= mod;
                }
            }
        }
        ll val = n * pw(2, mod - 2);
        b[0] -= coef;
        ll inv = pw(val, mod - 2);
        for(int i = 0 ; i < n ; ++ i) {
            if(i) putchar(' ');
            printf("%lld", (b[i] * inv % mod + mod) % mod);
        }
    }
}

int main() {
//    freopen("b.in", "r", stdin);
//    freopen("b.out", "w", stdout);
    scanf("%d", &n);
    
    fwt :: runprog();
    return 0;

    // if(n <= 300) {
    //     sol();
    //     getinv();
    // } else if(n <= 2500) {
    //     sol();
    //     n2_runit();
    // } else {
    //     fwt :: runprog();
    //     return 0;
    // }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     scanf("%lld", &b[i]);
    //     b[i] %= mod;
    // }
    // for(int i = 1 ; i <= n ; ++ i) {
    //     for(int k = 1 ; k <= n ; ++ k) {
    //         (c[i] += a[i][n + k] * b[k] % mod) %= mod;
    //     }
    // }

    // for(int i = 1 ; i <= n ; ++ i) {
    //     if(c[i] < 0) c[i] += mod;
    //     printf("%lld ", c[i]);
    // }
}
