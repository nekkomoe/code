#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5010, mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int n, k;

ll a[N], b[N], c[N];

int main() {
    scanf("%d%d", &n, &k);
    
    b[0] = 1, b[1] = k;
    for(int i = 2 ; i <= n ; ++ i)
        b[i] = (k + i - 1) * b[i - 1] % mod * pw(i, mod - 2) % mod;

    for(int i = 0 ; i < n ; ++ i)
        scanf("%lld", &a[i]);

    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j < n ; ++ j)
            if(i + j < n)
                (c[i + j] += a[i] * b[j] % mod) %= mod;

    for(int i = 0 ; i < n ; ++ i)
        printf("%lld\n", (c[i] + mod) % mod);
}

