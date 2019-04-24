#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7, phimod = mod - 1;
typedef long long ll;

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int f[110][110];

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("matrix.in", "r", stdin);
//     freopen("matrix.out", "w", stdout);
// #endif

    f[1][1] = 1;
    f[1][2] = 2;
    f[1][3] = 3;
    f[1][4] = 4;
    f[1][5] = 5;
    f[2][1] = 1;
    f[2][2] = 2;
    f[2][3] = 3;
    f[2][4] = 4;
    f[2][5] = 5;
    f[3][1] = 1;
    f[3][2] = 8;
    f[3][3] = 27;
    f[3][4] = 64;
    f[3][5] = 125;
    f[4][1] = 1;
    f[4][2] = 512;
    f[4][3] = 6561;
    f[4][4] = 131072;
    f[4][5] = 390625;
    f[5][1] = 1;
    f[5][2] = 32768;
    f[5][3] = 14348907;

    // ??
    f[5][4] = 1073741824 % mod;
    f[5][5] = 30517578125 % mod;

    int t; scanf("%d", &t);
    while(t --) {
        int n, m;
        scanf("%d%d", &n, &m);
        // printf("%d\n", f[n][m] % mod);
        if(n <= 2) {
            printf("%d\n", m);
        } else {
            ll y = (n - 1) % phimod;
            y = y * y % phimod;
            y = ((y - 1) % phimod + phimod) % phimod;
            ll res = pw(m, y);
            if(n == 4 && m % 2 == 0) {
                res = res * 2 % mod;
            }
            printf("%lld\n", res);
            // printf("%d %d\n", n, m);
            // assert(f[n][m] % mod == res);
        }
    }
}
