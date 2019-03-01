// luogu-judger-enable-o2
#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 1e6 + 10, mod = 998244353, g[2] = { 3, (mod + 1) / 3 };

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll f[N], fac[N], invfac[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
void ntt(ll *a, int ty, int n) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[ty], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }

    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(ty) a[i] = a[i] * inv % mod;
    }
}

ll a[N], res[N], A[N], B[N];

void mul(ll *a, ll *b, int n, int len) {

    for(int i = 0 ; i < len ; ++ i) A[i] = a[i], B[i] = b[i];
    // A[0] = A[1] = A[2] = 1;
    // B[0] = B[1] = B[2] = 1;
    
    ntt(A, 0, len), ntt(B, 0, len);
    for(int i = 0 ; i < len ; ++ i) A[i] = A[i] * B[i] % mod;
    ntt(A, 1, len);

    // cout << len << endl;
    // for(int i = 0 ; i <= 10 ; ++ i) cout << (A[i] + mod) % mod << ' '; exit(0);

    for(int i = 0 ; i <= n ; ++ i) a[i] = A[i];
}

int n, m;

ll get(ll m, ll T) {

    memset(a, 0, sizeof a);
    memset(res, 0, sizeof res);
    int len = 1; while(len <= 2 * n) len <<= 1;
    res[0] = 1;
    for(int i = 0 ; i < m ; ++ i) a[i] = invfac[i];

    for( ; T ; T >>= 1, mul(a, a, n, len)) {
        if(T & 1) {
            mul(res, a, n, len);
        }
    }

    return res[n - 2] * fac[n - 2] % mod;
}

int main() {
    init(N - 10);
    scanf("%d%d", &n, &m);
    // cout << get(m, n) << ' ' << get(m - 1, n) << endl;
    printf("%lld\n", ((get(m, n) - get(m - 1, n)) % mod + mod) % mod);
}
