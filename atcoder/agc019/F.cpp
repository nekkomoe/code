#include "bits/stdc++.h"
using namespace std;
const int mod = 998244353;
typedef long long ll;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
 
ll inv(ll n) {
    return pw(n, mod - 2);
}
 
const int N = 1e6 + 10;
 
ll fac[N], invfac[N], ans;
int n, m;
ll C(int n, int m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
ll calc(int n, int m) {
    return C(n + m, n);
}
 
int main() {
    scanf("%d%d", &n, &m);
    fac[0] = invfac[0] = 1;
    int lim = N - 1;
    for(int i = 1 ; i <= lim ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[lim] = pw(fac[lim], mod - 2);
    for(int i = lim - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    ll inv2 = inv(2);
    for(int i = 1 ; i <= min(n, m) ; ++ i) {
        ans = (ans + calc(i, i) * calc(n - i, m - i) % mod * inv2 % mod) % mod;
    }
    ans = ans * inv(calc(n, m)) % mod;
    ans = (ans + max(n, m)) % mod;
    printf("%lld\n", (ans + mod) % mod);
}
