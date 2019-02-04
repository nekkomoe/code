#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110;

ll f[N][N][N], g[N][N];

int n, k, a[N], ch[N][2], sta[N], top, fa[N];

int dfs(int u) {
    if(!u) return 0;
    int lc = ch[u][0], rc = ch[u][1];
    int lefwid = dfs(lc), rigwid = dfs(rc);
    int width = lefwid + 1 + rigwid, height = a[u] - a[fa[u]];
    
    f[u][0][0] = 0;
    memset(g, 0xcf, sizeof g);
    g[0][0] = 0;
    for(int i = 0 ; i <= k && i <= lefwid; ++ i) {
        for(int j = 0 ; i + j <= k && j <= rigwid ; ++ j) {
            // 左边i刀，右边j刀
            for(int x = 0 ; x <= lefwid ; ++ x) {
                for(int y = 0 ; y <= rigwid ; ++ y) {
                    g[i + j][x + y] = max(g[i + j][x + y], f[lc][i][x] + f[rc][j][y] + (ll) height * (x + y));
                }
            }
        }
    }
    
    for(int i = 0 ; i <= k && i <= width ; ++ i) {
        for(int x = 0 ; x <= width ; ++ x) {
            f[u][i][x] = max(f[u][i][x], g[i][x]);
            if(i + 1 <= min(k, width)) {
                f[u][i + 1][width] = max(f[u][i + 1][width], g[i][x] + (ll) (width - x) * height);
            }
        }
    }
    return width;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    memset(f, 0xcf, sizeof f);
    f[0][0][0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        while(top && a[sta[top]] > a[i]) {
            ch[i][0] = sta[top];
            -- top;
        }
        if(top) ch[sta[top]][1] = i;
        sta[++ top] = i;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            if(ch[i][j]) {
                fa[ch[i][j]] = i;
            }
        }
    }
    dfs(sta[1]);
    ll ans = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        ans = max(ans, f[sta[1]][k][i]);
    }
    printf("%lld\n", ans);
}


/*

f[i][j][k]: 以i为根的子树，切了j刀，底面长为k，面积的最大值

*/
