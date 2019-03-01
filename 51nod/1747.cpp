#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 510, mod = 998244353;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int n;

ll inv[N], b[N], c[N], a[N][N];

void init(int n) {
    inv[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) inv[i] = pw(i, mod - 2);
    b[0] = 1, c[0] = -1;
    for(int i = 1 ; i <= n ; ++ i) {
        b[i] = (1 - i * b[i - 1] % mod) % mod;
        c[i] = -i * c[i - 1] % mod;
    }
}

void runprog() {
    scanf("%d", &n);
    for(int i = 0 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            a[i][j] = inv[i + j + 1];
        }
        a[i][n + 1] = b[i];
        a[i][n + 2] = c[i];
    }
    for(int i = 0 ; i <= n ; ++ i) {
        if(a[i][i] == 0) {
            int id = i;
            for(int j = i + 1 ; j <= n ; ++ j) {
                if(a[j][i]) {
                    id = j;
                    break;
                }
            }
            for(int j = i ; j <= n + 2 ; ++ j) {
                swap(a[i][j], a[id][j]);
            }
        }
        if(a[i][i] < 0) a[i][i] += mod;
        ll inv = pw(a[i][i], mod - 2);
        for(int j = i ; j <= n + 2 ; ++ j) a[i][j] = a[i][j] * inv % mod;
        for(int j = 0 ; j <= n ; ++ j) {
            if(i == j || !a[j][i]) continue;
            ll prod = a[j][i];
            for(int k = i ; k <= n + 2 ; ++ k) {
                a[j][k] = (a[j][k] - a[i][k] * prod % mod) % mod;
            }
        }
    }
    for(int i = 0 ; i <= n ; ++ i) {
        printf("%lld %lld\n", (a[i][n + 1] % mod + mod) % mod, (a[i][n + 2] % mod + mod) % mod);
    }
}

int main() {
    init(500);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
