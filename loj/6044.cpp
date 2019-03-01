#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

const int N = 5e5 + 10;

int n, k, p, C[1010][1010];

ll fac[N], invfac[N];

ll getc(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % p * invfac[n - m] % p;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) {
        if(b & 1) {
            r = r * a % p;
        }
    }
    return r % p;
}

int main() {
    scanf("%d%d%d", &n, &k, &p);
    if(n <= 1000) {
        C[0][0] = 1;
        for(int i = 1 ; i <= n ; ++ i) {
            C[i][0] = 1;
            for(int j = 1 ; j <= i ; ++ j) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % p;
            }
        }
        int m = n - k;
        ll ans = pw(k, m - 1) * pw(m, k - 1) % p * C[n - 1][k - 1] % p;
        printf("%lld\n", (ans % p + p) % p);
    } else {
        fac[0] = invfac[0] = 1;
        for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % p;
        invfac[n] = pw(fac[n], p - 2);
        for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % p;
        int m = n - k;
        ll ans = pw(k, m - 1) * pw(m, k - 1) % p * getc(n - 1, k - 1) % p;
        printf("%lld\n", (ans % p + p) % p);
    }
}
