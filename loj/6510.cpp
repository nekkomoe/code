#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

int n, m, sta[N], insta[N], vis[N], col[N], col_cnt;
int U[N], V[N], from[N];
ll w[N], in[N], ans;

const ll inf = 1e15 + 10;

void dfs(int u) {
    if(!u || from[u] == -1) return ;
    vis[u] = insta[u] = 1;
    if(!vis[from[u]]) dfs(from[u]);
    else if(insta[from[u]]) {
        col[u] = ++ col_cnt;
        for(int v = from[u] ; v != u ; v = from[v]) col[v] = col_cnt;
    }
    insta[u] = 0;
    if(!col[u]) col[u] = ++ col_cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%lld", &U[i], &V[i], &w[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        U[++ m] = 0, V[m] = i, w[m] = inf;
    }
    while(1) {
        for(int i = 1 ; i <= n ; ++ i) in[i] = 2 * inf, from[i] = -1;
        for(int i = 1 ; i <= m ; ++ i) {
            if(w[i] < in[V[i]]) {
                in[V[i]] = w[i];
                from[V[i]] = U[i];
            }
        }
        for(int i = col_cnt = 0 ; i <= n ; ++ i) vis[i] = col[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            ans += in[i];
            if(!vis[i]) dfs(i);
        }
        if(n == col_cnt) break;
        int q = 0;
        for(int i = 1 ; i <= m ; ++ i) {
            if(col[U[i]] != col[V[i]]) {
                w[++ q] = w[i] - in[V[i]];
                U[q] = col[U[i]];
                V[q] = col[V[i]];
            }
        }
        m = q, n = col_cnt;
    }
    if(ans >= 2 * inf) puts("-1");
    else printf("%lld\n", ans - inf);
}
