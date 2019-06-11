#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 1e9 + 7, p = mod;
int n; ll k, a[N], b[N], f[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) {
        if(b & 1) {
            r = r * a % p;
        }
    }
    return r;
}
int main() {
    scanf("%d%lld", &n, &k), k %= mod;
    b[0] = 1, b[1] = k;
    for(int i = 2 ; i <= n ; ++ i)
        b[i] = (k + i - 1) * b[i - 1] % mod * pw(i, mod - 2) % mod;
    for(int i = 0 ; i < n ; ++ i)
        scanf("%lld", &a[i]);
    for(int i = 0 ; i < n ; ++ i)
        for(int j = 0 ; j < n ; ++ j)
            (f[i + j] += a[i] * b[j] % mod) %= mod;
    for(int i = 0 ; i < N ; ++ i)
        a[i] = f[i];
    for(int i = 0 ; i < n ; ++ i)
        printf("%lld ", (a[i] + mod) % mod);
}
