#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

struct P {
    int x, y;
} q[50000], p[50000], t;

P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}

int operator * (P a, P b) {
    return a.x * b.y - b.x * a.y;
}

bool operator < (P a, P b) {
    return (a - t) * (b - t) < 0;
}

int vis[N][N], f[N][N], n, k, m;

int main() {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d%d", &q[i].x, &q[i].y);
    for(int i = 1 ; i <= k ; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
    t = q[1];
    sort(q + 2, q + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        t = q[i];
        sort(p + 1, p + 1 + k);
        int res = 0;
        for(int j = i + 1 ; j <= n ; ++ j) {
            while(res < k && (p[res + 1] - t) * (q[j] - t) < 0) res ++;
            if((res & 1) || (p[res + 1] - t) * (q[j] - t) == 0) continue;
            vis[i][j] = vis[j][i] = 1;
        }
        f[i][i + 1] = 1;
    }
    
    for(int len = 2 ; len <= n ; ++ len) {
        for(int i = 1 ; i + len - 1 <= n ; ++ i) {
            int j = i + len - 1;
            for(int k = i + 1 ; k < j ; ++ k) {
                if(vis[i][k] && vis[k][j]) {
                    f[i][j] = (f[i][j] + (long long) f[i][k] * f[k][j]) % m;
                }
            }
        }
    }
    printf("%d\n", f[1][n]);
}
