#include <bits/stdc++.h>

using namespace std;

const int N = 21;

struct P {
    int x, y;
} p[N];

int operator ^ (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

int operator * (P a, P b) {
    return a.x * b.x + a.y * b.y;
}

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

int check(P a, P b, P c) {
    a = a - c, b = b - c;
    return !(a ^ b) && (a * b <= 0);
}

int n, f[N][1 << N], g[N][N], ans, bn[1 << N];

const int mod = 100000007;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
    for(int i = 1 ; i < (1 << n) ; ++ i) bn[i] = bn[i >> 1] + (i & 1);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            for(int k = 1 ; k <= n ; ++ k) {
                if(i != k && j != k && check(p[i], p[j], p[k])) {
                    g[i][j] |= (1 << (k - 1));
                    g[j][i] |= (1 << (k - 1));
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) f[i][1 << (i - 1)] = 1;
    for(int s = 1 ; s < (1 << n) ; ++ s) {
        for(int i = 1 ; i <= n ; ++ i) {
            if(f[i][s]) {
                for(int j = 1 ; j <= n ; ++ j) {
                    if(!(s & (1 << (j - 1))) && (s & g[i][j]) == g[i][j]) {
                        (f[j][s | (1 << (j - 1))] += f[i][s]) %= mod;
                    }
                }
            }
        }
    }
    for(int s = 1 ; s < (1 << n) ; ++ s) if(bn[s] >= 4) {
        for(int i = 1 ; i <= n ; ++ i) {
            (ans += f[i][s]) %= mod;
        }
    }
    printf("%d\n", ans);
}
