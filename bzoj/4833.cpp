#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 3e6 + 10;
 
int n; ll fib[N], g[N], cnt[N], ans, mod;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
 
int main() {
    scanf("%*d");
    while(scanf("%d%lld", &n, &mod) == 2) {
        fib[1] = 1, fib[2] = 2, ans = 0;
        for(int i = 3 ; i <= n ; ++ i) fib[i] = (2 * fib[i - 1] + fib[i - 2]) % mod;
        for(int i = 1 ; i <= n ; ++ i) g[i] = fib[i];
        for(ll i = 1 ; i <= n ; ++ i)
            for(ll j = 2, inv = pw(g[i], mod - 2) ; i * j <= n ; ++ j)
                g[i * j] = g[i * j] * inv % mod;
        g[0] = 1;
        for(ll i = 1 ; i <= n ; ++ i)
            g[i] = g[i - 1] * g[i] % mod,
            ans = (ans + i * g[i] % mod) % mod;
        printf("%lld\n", (ans % mod + mod) % mod);
    }
}
