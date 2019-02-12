#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 4e5 + 10, mod = 998244353;

int n, m;
ll f[N], fac[N], invfac[N], a[N], b[N], c[N], d[N], e[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

vector<int> g[N]; int fa[N];

void dfs(int u, int fa) {
    :: fa[u] = fa;
    a[u] = 1;
    for(int v: g[u]) {
        if(v == fa) continue;
        dfs(v, u);
        a[u] += a[v];
    }
}

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

ll Cn_1k[N];

namespace CALC {
    ll p[N], X[N * 10], Y[N * 10], f[N * 10];
    int a[N], len, inv;
    const int g[2] = { 3, (mod + 1) / 3 };
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod)
            if(b & 1)
                r = r * a % mod;
        return r;
    }
    int rev(int x, int n) {
        int res = 0;
        for(int i = 0 ; (1 << i) < n ; ++ i) {
            res = (res << 1) | ((x >> i) & 1);
        }
        return res;
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
        for(int i = 0 ; i < n ; ++ i) {
            a[i] = f[i];
            if(ty) a[i] = a[i] * inv % mod;
        }
    }

    void init() {
        len = 1; while(len < 4 * n) len <<= 1;
        for(int i = 0 ; i <= 2 * n ; ++ i) Y[i] = invfac[2 * n - i];
        inv = pw(len, mod - 2);
        ntt(Y, 0, len);
    }
    void sol() {
        int mx = 0;
        for(int i = 0 ; i < len ; ++ i) X[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) if(a[i] >= 0) ++ X[a[i]], mx = max(mx, a[i]);
        for(int i = 0 ; i <= mx ; ++ i) if(X[i]) (X[i] *= fac[i]) %= mod;
        ntt(X, 0, len);
        for(int i = 0 ; i < len ; ++ i) (X[i] *= Y[i]) %= mod;
        ntt(X, 1, len);
        for(int k = 1 ; k <= m ; ++ k) p[k] = X[2 * n + k] * invfac[k] % mod;
    }
}

void solf() {
    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] += n * C(n - 1, k - 1) % mod) %= mod;
    }
}

void solg() {
    for(int i = 1 ; i <= n ; ++ i) {
        CALC :: a[i] = n - a[i];
    }
    CALC :: sol();
    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] += n * C(n - 1, k) % mod) %= mod;
    }
    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] -= CALC :: p[k]) %= mod;
    }
}

void solh() {
    CALC :: a[1] = -1;
    for(int i = 2 ; i <= n ; ++ i) {
        CALC :: a[i] = n + a[i] - a[fa[i]];
    }
    CALC :: sol();

    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] -= CALC :: p[k]) %= mod;
    }

    CALC :: a[1] = -1;
    for(int i = 2 ; i <= n ; ++ i) {
        CALC :: a[i] = n - a[fa[i]];
    }
    CALC :: sol();

    for(int k = 1 ; k <= m ; ++ k) {
        (f[k] += CALC :: p[k]) %= mod;
    }    
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
    dfs(1, 0);

    CALC :: init();
    solf();
    solg();
    solh();

    for(int k = 1 ; k <= m ; ++ k) {
        f[k] = f[k] * pw(C(n, k), mod - 2) % mod;
        printf("%lld\n", (f[k] + mod) % mod);
    }
}
