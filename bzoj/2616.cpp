#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int T = 1e6 + 10, N = 510, mod = 1e9 + 7;

ll f[N][N], fac[T], invfac[T], g[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
}

int n, m, a[N], ch[N][2], sta[N], top, fa[N];

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int dfs(int u) {
    int width = 1, height = a[u] - a[fa[u]];
    f[u][0] = 1;
    for(int i = 0 ; i < 2 ; ++ i) {
        int v = ch[u][i];
        if(!v) continue;
        int wid = dfs(v);
        for(int j = 0 ; j <= width + wid ; ++ j) {
            g[j] = 0;
        }
        for(int j = 0 ; j <= width ; ++ j) {
            for(int k = 0 ; k <= wid && j + k <= m ; ++ k) {
                (g[j + k] += f[u][j] * f[v][k] % mod) %= mod;
            }
        }
        width += wid;
        for(int j = 0 ; j <= width ; ++ j) {
            f[u][j] = g[j];
        }
    }
    for(int i = min(m, width) ; ~ i ; -- i) {
        ll sum = 0;
        for(int j = 0 ; j <= i ; ++ j) {
            (sum += f[u][i - j] * fac[j] % mod * C(width - (i - j), j) % mod * C(height, j) % mod) %= mod;
        }
        f[u][i] = sum;
    }
    return width;
}

int main() {
    init(1e6);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        while(top && a[sta[top]] > a[i]) {
            ch[i][0] = sta[top];
            -- top;
        }
        if(top) ch[sta[top]][1] = i;
        sta[++ top] = i;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            if(ch[i][j]) {
                fa[ch[i][j]] = i;
            }
        }
    }
    dfs(sta[1]);
    printf("%lld\n", f[sta[1]][m]);
}
