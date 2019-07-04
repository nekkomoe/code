#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

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

void upd(int &a, int b) {
    a = (a + b) % mod;
}

int f[3010][3010][2];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    f[0][0][1] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        f[0][i][0] = 1;
    }
    for(int i = 0 ; i < m ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            for(int k = 0 ; k <= 1 ; ++ k) {
                if(j) {
                    upd(f[i + 1][j - 1][k | (j == 1)], f[i][j][k]);
                    upd(f[i + 1][j][k | (j == 1)], f[i][j][k]);
                }
                if(n - j) {
                    upd(f[i + 1][j + 1][k], f[i][j][k]);
                    upd(f[i + 1][j][k], f[i][j][k]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        upd(ans, f[m][i][1]);
    }
    printf("%d\n", (ans % mod + mod) % mod);
}
