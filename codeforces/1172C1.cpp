#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 2e5 + 10, M = 3010;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

ll s[2], sum, f[M][M], g[M][M];
int a[N], w[N], n, m;
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &w[i]);
        s[a[i]] += w[i];
        sum += w[i];
    }
    ll A = s[1], B = s[0];
    for(int i = m ; i >= 0 ; -- i) {
        f[i][m - i] = g[i][m - i] = 1;
        for(int j = min(m - i - 1ll, s[0]) ; j >= 0 ; -- j) {
            upd(f[i][j], (A + i + 1) * getinv(A + B + i - j) % mod * f[i + 1][j] % mod + (B - j) * getinv(A + B + i - j) % mod * f[i][j + 1] % mod);
            upd(g[i][j], (B - j - 1) * getinv(A + B + i - j) % mod * g[i][j + 1] % mod + (A + i) * getinv(A + B + i - j) % mod * g[i + 1][j] % mod);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%lld\n", (w[i] * (a[i] ? f : g)[0][0] % mod + mod) % mod);
    }
}
