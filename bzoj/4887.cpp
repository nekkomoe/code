#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 50;

const int mod = 2017;

int n, m, t;

ll a[N][N], x[N][N], tmp[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) scanf("%d%d", &u, &v), a[u][v] = a[v][u] = 1;
    for(int i = 0 ; i <= n ; ++ i) a[i][i] = 1;
    for(int i = 1 ; i <= n ; ++ i) a[i][0] = 1;
    scanf("%d", &t);
    for(int i = 0 ; i <= n ; ++ i) for(int j = 0 ; j <= n ; ++ j) x[i][j] = i == j;
    for( ; t ; t >>= 1) {
        if(t & 1) {
            memset(tmp, 0, sizeof tmp);
            for(int i = 0 ; i <= n ; ++ i) {
                for(int j = 0 ; j <= n ; ++ j) {
                    for(int k = 0 ; k <= n ; ++ k) {
                        tmp[i][j] += x[i][k] * a[k][j];
                        tmp[i][j] %= mod;
                    }
                }
            }
            memcpy(x, tmp, sizeof tmp);
        }
        memset(tmp, 0, sizeof tmp);
        for(int i = 0 ; i <= n ; ++ i) {
            for(int j = 0 ; j <= n ; ++ j) {
                for(int k = 0 ; k <= n ; ++ k) {
                    tmp[i][j] += a[i][k] * a[k][j];
                    tmp[i][j] %= mod;
                }
            }
        }
        memcpy(a, tmp, sizeof tmp);
    }
    ll ans = 0;
    for(int i = 0 ; i <= n ; ++ i) ans += x[1][i], ans %= mod;
    printf("%lld\n", ans);
}

