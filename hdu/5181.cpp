#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 310, mod = 1000000007;

int n, m;
ll f[N][N];
int g[N][N][N];
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

void add(int k, int x1, int y1, int x2, int y2) {
    g[x1][y1][k] ++;
    g[x2 + 1][y1][k] --;
    g[x1][y2 + 1][k] --;
    g[x2 + 1][y2 + 1][k] ++;
}

void runprog() {
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    scanf("%d%d", &n, &m);
    int flag = 0;
    for(int i = 1, x, y ; i <= m ; ++ i) {
        scanf("%d%d", &x, &y);
        if(x == y) {
            flag = 1;
        }
        if(x < y) {
            add(x, 1, y, x, n);
        }
        if(x > y) {
            // [1, y + 1] * [x, n]
            for(int k = y + 1 ; k <= x ; ++ k) {
                add(k, 1, x, y, n);
            }
        }
    }
    if(flag) {
        puts("0");
        return ;
    }

    for(int k = 1 ; k <= n ; ++ k) {
        for(int i = 1 ; i <= n ; ++ i) {
            for(int j = 1 ; j <= n ; ++ j) {
                g[i][j][k] += g[i - 1][j][k] + g[i][j - 1][k] - g[i - 1][j - 1][k];
            }
        }
    }

    for(int i = 1 ; i <= n + 1 ; ++ i) {
        f[i][i] = f[i][i - 1] = 1;
    }
    for(int len = 2 ; len <= n ; ++ len) {
        for(int i = 1 ; i <= n ; ++ i) {
            int j = i + len - 1;
            if(j > n) {
                break;
            }
            for(int k = i ; k <= j ; ++ k) {
                if(g[i][j][k] == 0) {
                    upd(f[i][j], f[i][k - 1] * f[k + 1][j] % mod);
                }
            }
        }
    }
    printf("%lld\n", f[1][n]);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
