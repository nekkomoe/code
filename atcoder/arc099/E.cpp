#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 710;
int a[N][N], flag, n, m, col[N], size[3];
bitset<N> vis;
void dfs(int u, int c) {
    col[u] = c;
    ++ size[c];
    for(int v = 1 ; v <= n ; ++ v) {
        if(!a[u][v] && v != u) {
            if(col[v]) {
                if(col[v] == c) {
                    flag = 1;
                    return ;
                }
            } else {
                dfs(v, 3 - c);
            }
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        a[u][v] = a[v][u] = 1;
    }
    vis[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if(col[i]) continue;
        size[1] = size[2] = 0;
        dfs(i, 1);
        vis = (vis << size[1]) | (vis << size[2]);
    }
    if(flag == 1) return puts("-1"), 0;
    ll ans = (ll) n * n;
    for(int i = 1 ; i <= n ; ++ i) {
        if(vis[i]) {
            ans = min(ans, (ll) i * (i - n) + (ll) n * (n - 1) / 2);
        }
    }
    printf("%lld\n", ans);
}
