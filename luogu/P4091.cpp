#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10, mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
const ll G[2] = { 3, pw(3, mod - 2) }; 

int n;
ll fac[N], invfac[N], a[N], f[N], g[N], h[N];

int rev(int x, int n) {
    int res = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i)   
        res = (res << 1) | ((x >> i) & 1);
    return res;
}

void ntt(ll *src, int len, int ty) {
    for(int i = 0 ; i < len ; ++ i) a[rev(i, len)] = src[i];
    
    for(int i = 2 ; i <= len ; i <<= 1) {
        ll wn = pw(G[ty], (mod - 1) / i);
        for(int j = 0 ; j < len ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = a[k], v = w * a[k + i / 2];
                a[k] = (u + v) % mod;
                a[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }
    
    ll inv = pw(len, mod - 2);
    for(int i = 0 ; i < len ; ++ i) {
        src[i] = a[i];
        if(ty) {
            src[i] = src[i] * inv % mod;
        }
    }
}

int main() {
    scanf("%d", &n);
    ll ans = 0;
    
    int len = 1; while(len <= 2 * (n + 1) + 10) len <<= 1;
    
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= len ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[len] = pw(fac[len], mod - 2);
    for(int i = len - 1 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    
    for(int i = 0 ; i <= n ; ++ i) {
        f[i] = (i & 1 ? -1 : 1) * invfac[i] % mod;
        g[i] = i == 0 ? 1 : i == 1 ? n + 1 : (pw(i, n + 1) - 1) % mod * pw(fac[i] * (i - 1) % mod, mod - 2) % mod;
    }
    
    ntt(f, len, 0), ntt(g, len, 0);
    for(int i = 0 ; i < len ; ++ i) f[i] = f[i] * g[i] % mod;
    ntt(f, len, 1);
    
    for(int i = 0 ; i <= n ; ++ i)
        ans = (ans + pw(2, i) * fac[i] % mod * f[i] % mod) % mod;
    printf("%lld\n", (ans % mod + mod) % mod);
} 

