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

int n, m;
double f[1010][1010], ans;
int a[N];

int main() {

    scanf("%d%d", &n, &m);

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            f[i][j] = a[i] > a[j];
        }
    }

    for(int t = 1 ; t <= m ; ++ t) {
        int x, y; scanf("%d%d", &x, &y);
        for(int i = 1 ; i <= n ; ++ i) {
            f[x][i] = f[y][i] = 0.5 * (f[x][i] + f[y][i]);
            f[i][x] = f[i][y] = 1 - f[x][i];
        }
        f[x][y] = f[y][x] = 0.5;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            ans += f[i][j];
        }
    }
    printf("%.10lf\n", ans);
}
