#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
unsigned n, m, X, Y, Z, W, f[int(5e6) * 3 + 10], a[int(1e5) + 10][21], lg[int(1e5) + 10];

unsigned get() {
    X = X ^ (X << 11);
    X = X ^ (X >> 4);
    X = X ^ (X << 5);
    X = X ^ (X >> 14);
    W = X ^ (Y ^ Z);
    X = Y;
    Y = Z;
    Z = W;
    return Z;
}

void chkmax(unsigned &x, unsigned y) {
    x = max(x, y);
}

void runprog() {
    scanf("%d%d%d%d%d", &n, &m, &X, &Y, &Z);
    for(int i = 1 ; i <= 3 * m ; ++ i) {
        f[i] = get();
    }

    for(int i = 1 ; i <= m ; ++ i) {
        unsigned l = f[3 * i - 2] % n + 1, r = f[3 * i - 1] % n + 1;
        if(l > r) swap(l, r);
        unsigned w = f[3 * i] % (1 << 30);
        unsigned k = lg[r - l + 1];
        chkmax(a[l][k], w);
        chkmax(a[r - (1 << k) + 1][k], w);
    }

    for(int j = lg[n] ; j ; -- j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            chkmax(a[i][j - 1], a[i][j]);
            chkmax(a[i + (1 << (j - 1))][j - 1], a[i][j]);
        }
    }

    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ans ^= (ll) i * a[i][0];
    }
    printf("%lld\n", ans);
    for(int j = 0 ; j <= lg[n] ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            a[i][j] = 0;
        }
    }
}

void init(int n) {
    for(int i = 2 ; i <= n ; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }
}

int main() {
    init(1e5);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
