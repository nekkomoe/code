#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 2010, MXL = 11;

int n, m, p;

int f[2][1 << (MXL + 1)][2];

void sol(int l) {
    memset(f, 0, sizeof f), p = 0;
    int lim = max(n, m);
    int maxs = 1 << MXL;
    f[p][0][0] = 1;
    for(int i = 1 ; i <= lim ; ++ i) {
        p ^= 1;
        memset(f[p], 0, sizeof f[p]);
        for(int s = 0 ; s < maxs ; ++ s) {
            for(int t = 0 ; t < 2 ; ++ t) {
                if(i <= n) {
                    (f[p][s ^ i][t] += f[!p][s][t]) %= mod;
                }
                if(i <= m) {
                    (f[p][s ^ i][t ^ ((i >> l) & 1)] += f[!p][s][t]) %= mod;
                }
                (f[p][s][t] += f[!p][s][t]) %= mod;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    ll ans = 0;
    for(int l = 0 ; l <= MXL ; ++ l) {
        sol(l);
        for(int s = (1 << l) ; s < (1 << (l + 1)) ; ++ s) {
            ans = ((ll) ans + f[p][s][1]) % mod;
        }
    }
    printf("%d\n", ans);
}
