#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 998244353, g[2] = { 3, (p + 1) / 3 }, N = 7e4;

int n, k;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}

ll fac[N], invfac[N];

ll C(ll up, ll down) {
    return up < down ? 0 : fac[up] * invfac[down] % p * invfac[up - down] % p;
}

ll ntt_tmp[N];

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) r = (r << 1) | ((x >> i) & 1);
    return r;
}

ll ntt(ll *a, int n, int ty) {
    for(int i = 0 ; i < n ; ++ i) ntt_tmp[rev(i, n)] = a[i];
    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (p - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = ntt_tmp[k], v = w * ntt_tmp[k + i / 2] % p;
                ntt_tmp[k] = (u + v) % p;
                ntt_tmp[k + i / 2] = ((u - v) % p + p) % p;
                w = w * wn % p;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        a[i] = ntt_tmp[i];
        if(ty == 1) a[i] = a[i] * pw(n, p - 2) % p;
    }
}

ll F[N], x[N], y[N];

void e2ix(int k, int n) {
    memset(y, 0, sizeof y);
    for(int i = 0 ; i < n ; ++ i)
        y[i] = pw(2, i * k) * x[i] % p;
}

ll _x[N], _y[N];

void mul(ll *a, ll *b, int _n) {
    int n = 1; while(n < (2 * _n)) n <<= 1;
    for(int i = 0 ; i < _n ; ++ i) _x[i] = a[i], _y[i] = b[i];
    for(int i = _n ; i < n ; ++ i) _x[i] = _y[i] = 0;
    ntt(_x, n, 0), ntt(_y, n, 0);
    for(int i = 0 ; i < n ; ++ i) _x[i] = (_x[i] * _y[i]) % p;
    ntt(_x, n, 1);
    for(int i = 0 ; i < n ; ++ i) a[i] = _x[i];
}

void sol(int n) {
    for(int i = 1 ; i <= k ; ++ i) x[i] = invfac[i];
    int now = 0, pw2 = 1;
    F[0] = 1;
    for( ; n ; n >>= 1, pw2 <<= 1) {
        if(n & 1) {
            e2ix(now, k + 1);
            mul(F, y, k + 1);
            now |= pw2;
        }
        e2ix(pw2, k + 1);
        mul(x, y, k + 1);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        fac[i] = fac[i - 1] * i % p;
        invfac[i] = pw(fac[i], p - 2);
    }
    sol(n);
    ll ans = 0;
    for(int i = 1 ; i <= k ; ++ i) {
        ans = (ans + F[i] * C(k, i) % p * fac[i] % p) % p;
    }
    printf("%lld\n", ans);
}
