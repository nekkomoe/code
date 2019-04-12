#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

ll f[N], g[N], sum[N];

int n, k, a[N], ch[N][2], sta[N], top, fa[N];

int dfs(int u) {
    if(!u) return 0;
    int lc = ch[u][0], rc = ch[u][1];
    int lefwid = dfs(lc), rigwid = dfs(rc);
    int width = lefwid + 1 + rigwid, height = a[u] - a[fa[u]];
    sum[u] = sum[lc] + sum[rc] + a[u];

    f[u] = f[lc] + f[rc];
    ll rest = (ll) height * width - (g[lc] + g[rc]);
    if(rest > 0) f[u] += (rest + k - 1) / k;
    g[u] = f[u] * k - (sum[u] - (ll) a[fa[u]] * width);
    
    return width;
}

int main() {
    while(scanf("%d%d", &n, &k) == 2) {
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%d", &a[i]);
        }
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
        printf("%lld\n", f[sta[1]]);
    }
}
