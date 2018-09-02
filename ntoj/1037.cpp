#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, deg[N], vis[N], to[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &to[i]);
        ++ deg[to[i]];
    }
    queue<int> q;
    for(int i = 1 ; i <= n ; ++ i) {
        if(!deg[i]) {
            q.push(i);
            vis[i] = 1;
        }
    }
    int ans = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        int v = to[u];
        if(!vis[v]) {
            vis[v] = 1;
            ++ ans;
            int w = to[v];
            if(! -- deg[w]) q.push(w), vis[w] = 1;
        }
    }
    for(int u = 1 ; u <= n ; ++ u) {
        if(!vis[u]) {
            int sz = 0;
            for(int x = u ; !vis[x] ; x = to[x]) vis[x] = 1, ++ sz;
            ans += sz / 2;
        }
    }
    printf("%d\n", ans);
}
