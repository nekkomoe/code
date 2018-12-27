#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, mod = 1e9 + 7;

int n, mx, a[N]; ll fib[N], g[N], cnt[N], ans = 1;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), mx = max(mx, a[i]), cnt[a[i]] ++;
    fib[1] = g[1] = 1; for(int i = 2 ; i <= mx ; ++ i) g[i] = fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    for(ll i = 1 ; i <= mx ; ++ i)
        for(ll j = 2, inv = pw(g[i], mod - 2) ; i * j <= mx ; ++ j)
            g[i * j] = g[i * j] * inv % mod;
    for(ll i = 1 ; i <= mx ; ++ i)
        for(ll j = 1 ; i * j <= mx ; ++ j)
            if(cnt[i * j]) {
                ans = ans * g[i] % mod;
                break;
            }
    printf("%lld\n", (ans % mod + mod) % mod);
}

