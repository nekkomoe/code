#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2510, mod = 2333;

ll Cmem[N][N], Fmem[N][N];

ll C(ll n, ll m) {
    if(m < 0 || n < m) return 0;
    if(n <= 2500) return Cmem[n][m];
    return C(n % mod, m % mod) * C(n / mod, m / mod) % mod;
}

ll f(ll n, ll k) {
    if(k < 0) return 0;
    else if(!n) return 1;
    else if(!k) return 1;
    else if(n <= 2500 && k <= 2500) {
        return Fmem[n][k];
    } else {
        return (
            f(n % mod, mod - 1) * f(n / mod, k / mod - 1) % mod
          + C(n / mod, k / mod) * f(n % mod, k % mod) % mod
        ) % mod;
    }
}

void Cinit(int n) {
    Cmem[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        Cmem[i][0] = 1;
        for(int j =  1 ; j <= i ; ++ j) {
            Cmem[i][j] = (Cmem[i - 1][j - 1] + Cmem[i - 1][j]) % mod;
        }
    }
    Fmem[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        Fmem[i][0] = 1;
    }
    for(int i = 0 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            Fmem[i][j] = (Cmem[i][j] + Fmem[i][j - 1]) % mod;
        }
    }
}

int main() {
    Cinit(2500);
    int T; scanf("%d", &T);
    while(T --) {
        ll n, k; scanf("%lld%lld", &n, &k);
        printf("%lld\n", (f(n, k) % mod + mod) % mod);
    }
}
