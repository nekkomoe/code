#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, inf = 0x3f3f3f3f;
int head[N], rest[N], to[N], tot;
int n, m, k, lz[N];
int dis[N], ans[N];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void bfs(int S) {
    for(int i = 1 ; i <= n ; ++ i) dis[i] = inf;
    dis[S] = 0;
    queue<int> q;
    q.push(S);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == inf) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) ans[i] = max(ans[i], dis[i]);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= k ; ++ i) scanf("%d", &lz[i]);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    for(int i = 1 ; i <= k ; ++ i) bfs(lz[i]);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d", ans[i]);
        if(i < n) putchar(' ');
    }
}
