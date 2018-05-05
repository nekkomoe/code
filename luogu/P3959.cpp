#include <bits/stdc++.h>

using namespace std;

int f[1 << 14], dis[14], a[14][14], lk[14][14], n, m, ans = 0x3f3f3f3f;

void dfs(int x) {
    for(int i = 1 ; i <= n ; ++ i) {
        if((x >> (i - 1)) & 1) {
            for(int j = 1 ; j <= n ; ++ j) {
                if(!((x >> (j - 1)) & 1) && lk[i][j]) {
                    if(f[1 << (j - 1) | x] > f[x] + dis[i] * a[i][j]) {
                        int t = dis[j];
                        dis[j] = dis[i] + 1;
                        f[1 << (j - 1) | x] = f[x] + dis[i] * a[i][j];
                        dfs(1 << (j - 1) | x);
                        dis[j] = t;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(a, 0x3f, sizeof a);
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        if(w < a[u][v]) {
            a[u][v] = a[v][u] = w;
            lk[u][v] = lk[v][u] = 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        memset(dis, 0x3f, sizeof dis);
        for(int j = 1 ; j < (1 << n) ; ++ j) f[j] = 0x3f3f3f3f;
        dis[i] = 1, f[1 << (i - 1)] = 0;
        dfs(1 << (i - 1));
        ans = min(ans, f[(1 << n) - 1]);
    }
    printf("%d\n", ans);
}
