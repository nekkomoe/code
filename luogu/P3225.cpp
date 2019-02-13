#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
const int N = 1100;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int T, n, m, vis[N], cut[N], id[N], cnt, tmp[N], K;
 
void init() {
    tot = 0;
    memset(head, 0, sizeof(head));
    cnt = 0;
    memset(cut, 0, sizeof(cut));
    memset(id, 0, sizeof(id));
    memset(tmp, 0, sizeof(tmp));
    K = 0;
    n = 0;
}
 
void dfs1(int u) {
    vis[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!vis[v] && v != K) {
            dfs1(v);
        }
    }
}
 
void dfs2(int u) {
    vis[u] = 1;
    if(id[u]) id[u] = -1;
    else id[u] = K;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!vis[v] && !cut[v]) {
            dfs2(v);
        }
    }
}
 
int main() {
    while(scanf("%d", &m) == 1 && m) {
        init();
        for(int i = 1, u, v ; i <= m ; ++ i) {
            scanf("%d%d", &u, &v);
            add(u, v), add(v, u);
            n = max(n, max(u, v));
        }
        for(int i = 1 ; i <= n ; ++ i) {
            memset(vis, 0, sizeof(vis));
            K = i;
            dfs1(i % n + 1);
            for(int j = 1 ; j <= n ; ++ j) {
                if(j != i && !vis[j]) {
                    cut[i] = 1;
                    break;
                }
            }
        }
        K = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if(cut[i]) {
                memset(vis, 0, sizeof(vis));
                for(int j = head[i] ; j ; j = rest[j]) {
                    int v = to[j];
                    if(!cut[v] && !vis[v]) {
                        ++ K;
                        dfs2(v);
                    }
                }
            }
        }
        for(int i = 1 ; i <= n ; ++ i) {
            if(id[i] != -1) {
                ++ tmp[id[i]];
            }
        }
        int ans = 0;
        long long tot = 1;
        for(int i = 1 ; i <= K ; ++ i) {
            if(tmp[i] != 0) {
                ++ ans;
                tot *= tmp[i];
            }
        }
        if(!ans) printf("Case %d: 2 %lld\n", ++ T, (long long)n * (n - 1) / 2);
        else printf("Case %d: %d %lld\n", ++ T, ans, tot);
    }
    return 0;
}
