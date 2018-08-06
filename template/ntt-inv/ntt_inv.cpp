#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 4e6 + 10;
const ll p = 998244353;
const ll g[2] = { 3, (p + 1) / 3};
ll a[N], b[N], f[N]; int n, m;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}
ll inv(ll x) {
    return pw(x, p - 2);
}
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
    return r;
}
void ntt(ll *a, int n, int t) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[t], (p - 1) / i);
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
        a[i] = f[i] % p;
        if(t) a[i] = a[i] * inv(n) % p;
    }
}

ll t[N], aa[N], h[N];

void sol(int n) {
    if(n == 1) {
        b[0] = inv(a[0]);
    } else {
        sol((n + 1) / 2);
        for(int i = 0 ; i < n ; ++ i) t[i] = 2 * b[i] % p, aa[i] = a[i];
        int len = 1; while(len <= 2 * n) len <<= 1;
        for(int i = n ; i <= len ; ++ i) aa[i] = 0;
        ntt(aa, len, 0), ntt(b, len, 0);
        for(int i = 0 ; i < len ; ++ i) h[i] = aa[i] * b[i] % p * b[i] % p;
        ntt(h, len, 1);
        for(int i = 0 ; i < n ; ++ i) b[i] = ((t[i] - h[i]) % p + p) % p;
        for(int i = n ; i < len ; ++ i) b[i] = 0;
    }
}

int main() {
    scanf("%d", &n), ++ n;
    for(int i = 0 ; i < n ; ++ i) scanf("%lld", &a[i]);
    sol(n);
    for(int i = 0 ; i < n - 1 ; ++ i) printf("%lld ", b[i]);
}