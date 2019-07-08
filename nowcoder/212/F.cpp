#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 60;

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

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n, m, a[N], b[N];
ll f[N][N][N * N], C[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &b[i]);
    }
    sort(b + 1, b + 1 + m);
    for(int i = 1 ; i <= m ; ++ i) {
        b[i] += b[i - 1];
    }
    int s = b[m];
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= m ; ++ j) {
            a[i] = max(a[i], s - (n - i) * (m - j) - b[j]);
        }
    }

    C[0][0] = 1;
    for(int i = 1 ; i <= 50 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= i ; ++ j) {
            upd(C[i][j], (C[i - 1][j - 1] + C[i - 1][j]) % mod);
        }
    }

    for(int i = 0 ; i <= n ; ++ i) {
        f[0][i][0] = a[i] ? 0 : C[n][i];
    }
    for(int i = 0 ; i < m ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            for(int k = a[j] ; k <= s - (n - j) * (i + 1) ; ++ k) {
                for(int t = 0 ; t <= n - j && k + t * (i + 1) <= s && k + t * (i + 1) >= a[j + t] ; ++ t) {
                    upd(f[i + 1][j + t][k + t * (i + 1)], f[i][j][k] * C[n - j][t] % mod);
                }
            }
        }
    }

    printf("%lld\n", (f[m][n][s] % mod + mod) % mod);
}
