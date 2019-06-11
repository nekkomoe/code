#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 510, pr[10] = { 2, 3, 5, 7, 11, 13, 17, 19 }, lim = 255;

int n, mod;
vector<int> g[N];
void upd(int &x, int y) {
    x = ((ll) x + y) % mod;
}
int f[1 << 9][1 << 9];
int h_a[1 << 9][1 << 9];
int h_b[1 << 9][1 << 9];

int main() {
    scanf("%d%d", &n, &mod);
    // [2, n]
    for(int i = 1 ; i < n ; ++ i) {
        int x = i + 1, s = 0;
        for(int j = 0 ; j < 8 ; ++ j) {
            if(x % pr[j] == 0) {
                s |= 1 << j;
                while(x % pr[j] == 0) x /= pr[j];
            }
        }
        g[x].push_back(s);
    }
    int lim = 1 << 8;
    f[0][0] = 1;

    for(int p = 0 ; p < g[1].size() ; ++ p) {
        int y = g[1][p];
        memcpy(h_a, f, sizeof f);
        memcpy(h_b, f, sizeof f);
        for(int i = lim ; i >= 0 ; -- i) {
            for(int j = lim ; j >= 0 ; -- j) {
                if((i & j) == 0) {
                    if((y & j) == 0) {
                        upd(h_a[i | y][j], h_a[i][j]);
                    }
                    if((y & i) == 0) {
                        upd(h_b[i][j | y], h_b[i][j]);
                    }
                }
            }
        }
        for(int i = 0 ; i <= lim ; ++ i) {
            for(int j = 0 ; j <= lim ; ++ j) {
                f[i][j] = ((ll) h_a[i][j] + h_b[i][j] - f[i][j]) % mod;
            }
        }
    }

    for(int x = 2 ; x <= n ; ++ x) {
        if(g[x].size()) {
            memcpy(h_a, f, sizeof f);
            memcpy(h_b, f, sizeof f);

            for(int p = 0 ; p < g[x].size() ; ++ p) {
                int y = g[x][p];
                for(int i = lim ; i >= 0 ; -- i) {
                    for(int j = lim ; j >= 0 ; -- j) {
                        if((i & j) == 0) {
                            if((y & j) == 0) {
                                upd(h_a[i | y][j], h_a[i][j]);
                            }
                            if((y & i) == 0) {
                                upd(h_b[i][j | y], h_b[i][j]);
                            }
                        }
                    }
                }
            }

            for(int i = 0 ; i <= lim ; ++ i) {
                for(int j = 0 ; j <= lim ; ++ j) {
                    f[i][j] = ((ll) h_a[i][j] + h_b[i][j] - f[i][j]) % mod;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0 ; i <= lim ; ++ i) {
        for(int j = 0 ; j <= lim ; ++ j) {
            if((i & j) == 0) {
                upd(ans, f[i][j]);
            }
        }
    }
    printf("%d\n", (ans % mod + mod) % mod);
}
