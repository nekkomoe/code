#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int mod; 
const int N = 310;

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

int n, nek;
ll f[N][N], C[N][N], g[N][N];

int main() {
    scanf("%d%d%d", &n, &nek, &mod);
    C[0][0] = 1;
    for(int i = 1 ; i <= n + 1 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= n + 1 ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    for(int j = 0 ; j <= nek ; ++ j) {
        f[1][j] = 1;
        g[1][j] = 1;
    }
    for(int j = nek ; j >= 0 ; -- j) {
        upd(g[1][j], g[1][j + 1]);
    }
    for(int i = 2 ; i <= n + 1 ; ++ i) {
        for(int j = 0 ; j <= nek ; ++ j) {
            for(int k = 1 ; k <= i - 1 ; ++ k) {
                if(i - 2 >= 0 && k - 1 >= 0) {
                    // for(int l = j + 1 ; l <= nek ; ++ l) {
                    //     upd(f[i][j], C[i - 2][k - 1] * f[i - k][j] % mod * f[k][l] % mod);
                    // }
                    upd(f[i][j], C[i - 2][k - 1] * f[i - k][j] % mod * g[k][j + 1] % mod);
                }
            }
            g[i][j] = f[i][j];
        }
        for(int j = nek ; j >= 0 ; -- j) {
            upd(g[i][j], g[i][j + 1]);
        }
    }
    printf("%lld\n", (f[n + 1][0] % mod + mod) % mod);
}
