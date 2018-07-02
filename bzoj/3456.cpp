#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1004535809;
const ll g[2] = { 3, 334845270 };
const int N = 263000;
 
ll f[N];
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}
ll inv(ll a) {
    return pw(a, p - 2);
}
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
    return r;
}
void ntt(ll *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (p - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % p;
                f[k] = (u + v) % p, f[k + i / 2] = ((u - v) % p + p) % p;
                w = w * wn % p;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty == 1) a[i] = a[i] * inv(n) % p;
    }
}
ll aa[N], t[N], a[N], b[N], h[N];
void sol(int n) {
    if(n == 1) {
        b[0] = inv(a[0]);
    } else {
        sol((n + 1) / 2);
        int len = 1; while(len <= 2 * n - 2) len <<= 1;
        for(int i = 0 ; i < n ; ++ i) aa[i] = a[i], t[i] = 2 * b[i] % p;
        ntt(aa, len, 0), ntt(b, len, 0);
        for(int i = 0 ; i < len ; ++ i) h[i] = aa[i] * b[i] % p * b[i] % p;
        ntt(h, len, 1);
        for(int i = 0 ; i < n ; ++ i) b[i] = ((t[i] - h[i]) % p + p) % p;
        for(int i = n ; i < len ; ++ i) b[i] = 0;
    }
}
int n;
ll fac[N], F[N], G[N], T[N], Ginv[N];
int main() {
    scanf("%d", &n);
    for(int i = fac[0] = 1 ; i < N ; ++ i) fac[i] = fac[i - 1] * i % p;
    for(int i = 1 ; i <= n ; ++ i) T[i] = pw(2, (ll) i * (i - 1) / 2) * inv(fac[i - 1]) % p;
    for(int i = 0 ; i <= n ; ++ i) G[i] = pw(2, (ll) i * (i - 1) / 2) * inv(fac[i]) % p, a[i] = G[i];
    sol(n + 10);
    for(int i = 0 ; i <= n ; ++ i) Ginv[i] = b[i];
    int len = 1; while(len <= n + 10) len <<= 1;
    ntt(Ginv, len, 0), ntt(T, len, 0);
    for(int i = 0 ; i < len ; ++ i) F[i] = Ginv[i] * T[i] % p;
    ntt(F, len, 1);
    printf("%lld\n", F[n] * fac[n - 1] % p);
}

