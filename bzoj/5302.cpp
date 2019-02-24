#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2010, mod = 1e9 + 7;

int n, q, p, d[N], tot, cnt[N];

ll ans[N], pw[int(1e6) + 10], f[N][N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int get(int x) {
    return lower_bound(d + 1, d + 1 + tot, x) - d;
}

int main() {
    scanf("%d%d%d", &n, &q, &p);
    for(int i = 1 ; i * i <= p ; ++ i) {
        if(p % i == 0) {
            d[++ tot] = i;
            if(p / i != i) {
                d[++ tot] = p / i;
            }
        }
    }
    sort(d + 1, d + 1 + tot);
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        ++ cnt[get(gcd(x, p))];
    }
    pw[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) pw[i] = pw[i - 1] * 2 % mod;
    f[0][tot] = 1;
    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = 1 ; j <= tot ; ++ j) {
            int x = get(gcd(d[i], d[j]));
            f[i][x] = (f[i][x] + f[i - 1][j] * (pw[cnt[i]] - 1) % mod) % mod;
            f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
        }
    }
    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = 1 ; j <= i ; ++ j) {
            if(d[i] % d[j] == 0) {
                ans[i] = (ans[i] + f[tot][j]) % mod;
            }
        }
    }
    for(int i = 1 ; i <= q ; ++ i) {
        int x; scanf("%d", &x);
        printf("%lld\n", ans[get(gcd(x, p))]);
    }
}
