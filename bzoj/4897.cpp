#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define chkmin(a, b) (a = min(a, b))

int n, cnt;
ll a, b, f[55][55][55][55], g[55][55], w[55], num[55];

inline ll sqr(ll x) {
    return x * x;
}

int main() {
    scanf("%d%lld%lld", &n, &a, &b);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &w[i]);
        num[i] = w[i];
    }
    memset(f, 0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);
    sort(num + 1, num + 1 + n);
    cnt = unique(num + 1, num + 1 + n) - num - 1;
    for(int i = 1 ; i <= n ; ++ i) {
        w[i] = lower_bound(num + 1, num + 1 + cnt, w[i]) - num;
        f[i][i][w[i]][w[i]] = 0;
        g[i][i] = a;
    }
    for(int len = 2 ; len <= n ; ++ len) {
        for(int i = 1 ; ; ++ i) {
            int j = i + len - 1;
            if(j > n) {
                break;
            }
            f[i][j][w[j]][w[j]] = g[i][j - 1];
            for(ll x = 1 ; x <= cnt ; ++ x) {
                for(ll y = x ; y <= cnt ; ++ y) {
                    chkmin(f[i][j][min(x, w[j])][max(y, w[j])], f[i][j - 1][x][y]);
                }
            }
            for(int k = i ; k < j ; ++ k) {
                for(ll x = 1 ; x <= cnt ; ++ x) {
                    for(ll y = x ; y <= cnt ; ++ y) {
                        chkmin(f[i][j][x][y], f[i][k][x][y] + g[k + 1][j]);
                    }
                }
            }
            for(ll x = 1 ; x <= cnt ; ++ x) {
                for(ll y = x ; y <= cnt ; ++ y) {
                    chkmin(g[i][j], a + f[i][j][x][y] + b * sqr(num[x] - num[y]));
                }
            }
        }
    }
    printf("%lld\n", g[1][n]);
}
