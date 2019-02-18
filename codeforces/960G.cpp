// nlog^2n
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 }, N = 1e6 + 10;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
ll f[N];
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
void ntt(ll *a, int n, int ty) {
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
ll a[N], b[N];

vector<ll> sol(int l, int r) {
    if(l == r) {
        vector<ll> res;
        res.push_back(l);
        res.push_back(1);
        return res;
    } else {
        int mid = (l + r) >> 1;
        vector<ll> A = sol(l, mid), B = sol(mid + 1, r), res;
        int len = r - l + 1;
        int n = 1; while(n < 2 * len) n <<= 1;
        for(int i = 0 ; i < n ; ++ i) a[i] = b[i] = 0;
        for(int i = 0 ; i < A.size() ; ++ i) a[i] = A[i];
        for(int i = 0 ; i < B.size() ; ++ i) b[i] = B[i];
        ntt(a, n, 0), ntt(b, n, 0);
        for(int i = 0 ; i < n ; ++ i) a[i] = a[i] * b[i] % mod;
        ntt(a, n, 1);
        for(int i = 0 ; i <= len ; ++ i) {
            res.push_back(a[i]);
        }
        res.resize(len + 1);
        return res;
    }
}

ll fac[N], invfac[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    if(!a || !b || a + b - 2 > n - 1) return puts("0"), 0;
    if(n == 1) return puts("1"), 0;
    init(a + b);
    vector<ll> S = sol(0, n - 2);
    ll ans = S[a + b - 2] * C(a + b - 2, a - 1) % mod;
    printf("%lld\n", (ans + mod) % mod);
}

// nlogn
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353, g[2] = { 3, (mod + 1) / 3 }, N = 1e6 + 10;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
ll f[N];
int rev(int x, int n) {
    int r = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i) {
        r = (r << 1) | ((x >> i) & 1);
    }
    return r;
}
void ntt(ll *a, int n, int ty) {
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
ll p[N], q[N];

void mul(int n) {
    ntt(p, n, 0), ntt(q, n, 0);
    for(int i = 0 ; i < n ; ++ i) p[i] = p[i] * q[i] % mod;
    ntt(p, n, 1);
}

ll fac[N], invfac[N];
void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll S[N], A[N];

void sol(int n) {
    if(n == 1) {
        S[1] = 1;
    } else if(n & 1) {
        sol(n - 1);
        for(int i = n ; i >= 0 ; -- i) {
            S[i] = (S[i - 1] + S[i] * (n - 1) % mod) % mod;
        }
    } else {
        sol(n / 2); int lef = n / 2;
        int len = 1; while(len < 4 * n) len <<= 1;
        for(int i = 0 ; i < len ; ++ i) p[i] = q[i] = 0;
        for(int i = 0 ; i <= lef ; ++ i) {
            p[i] = S[i] * fac[i] % mod;
            q[lef - i] = pw(lef, i) * invfac[i] % mod;
        }
        mul(len);
        for(int i = 0 ; i <= lef ; ++ i) p[i] = p[i + lef] * invfac[i] % mod;
        for(int i = lef + 1 ; i < len ; ++ i) p[i] = 0;
        for(int i = 0 ; i < len ; ++ i) q[i] = 0;
        for(int i = 0 ; i <= lef ; ++ i) q[i] = S[i];
        mul(len);
        for(int i = 0 ; i <= n ; ++ i) S[i] = p[i];
    }
}

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    if(!a || !b || a + b - 2 > n - 1) return puts("0"), 0;
    if(n == 1) return puts("1"), 0;
    init(N - 10);
    sol(n - 1);
    ll ans = S[a + b - 2] * C(a + b - 2, a - 1) % mod;
    printf("%lld\n", (ans + mod) % mod);
}

