#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 610, mod = 1e9 + 7;
int f[N][N][N];
void upd(int &x, ll y) {
    x = (x + y) % mod;
}

ll getfac(ll n) {
    ll r = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        r = r * i % mod;
    }
    return r;
}

int n, a[N], m, cnt;
int use[N], c[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= 2 * n ; i += 2) {
        if(a[i] == -1 && a[i + 1] == -1) {
            ++ cnt;
        } else if(a[i] != -1 && a[i + 1] != -1) {
            use[a[i]] = use[a[i + 1]] = -1; // 不使用
        } else if(a[i] != -1) {
            use[a[i]] = 1;
        } else if(a[i + 1] != -1) {
            use[a[i + 1]] = 1;
        }
    }
    for(int i = 1 ; i <= 2 * n ; ++ i) {
        if(use[i] == 1) {
            c[++ m] = 1;
        } else if(use[i] == 0) {
            c[++ m] = 0;
        }
    }
    f[m][0][0] = 1;
    for(int i = m ; i ; -- i) {
        for(int j = 0 ; j <= min(n, m) ; ++ j) {
            for(int k = 0 ; k <= min(n, m) ; ++ k) {
                if(c[i] == 1) {
                    upd(f[i - 1][j + 1][k], f[i][j][k]);
                    if(k) upd(f[i - 1][j][k - 1], f[i][j][k]);
                } else if(c[i] == 0) {
                    upd(f[i - 1][j][k + 1], f[i][j][k]);
                    if(k) upd(f[i - 1][j][k - 1], f[i][j][k]);
                    if(j) upd(f[i - 1][j - 1][k], (ll) f[i][j][k] * j % mod);
                }
            }
        }
    }
    printf("%lld\n", (f[0][0][0] * getfac(cnt) % mod + mod) % mod);
}
