#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 4e6 + 10;

typedef long long ll;

const ll p = 998244353ll, g[2] = {3, 332748118};

ll pw(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % p;
        b >>= 1, a = a * a % p;
    }
    return res;
}

int n, m, len;

ll a[N], b[N], f[N], inv;

int rev(int x, int n) {
    int res = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) (res <<= 1) |= (x >> i) & 1;
    return res;
}

void ntt(ll *t, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = t[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (p - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % p;
                f[k] = (u + v) % p;
                f[k + i / 2] = ((u - v) % p + p) % p;
                w = w * wn % p;
            }
        }
    }

    if(ty) for(int i = 0 ; i < n ; ++ i) t[i] = f[i] * inv % p;
    else for(int i = 0 ; i < n ; ++ i) t[i] = f[i];
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i < n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 0 ; i < m ; ++ i) scanf("%lld", &b[i]);
    n ++, m ++;
    for(len = 1 ; len <= n + m + 5 ; len <<= 1);
    inv = pw(len, p - 2);
    ntt(a, len, 0), ntt(b, len, 0);
    for(int i = 0 ; i < len ; ++ i) a[i] = a[i] * b[i] % p;
    ntt(a, len, 1);
    for(int i = 0 ; i < n + m - 1 ; ++ i) printf("%lld ", a[i]);
}

