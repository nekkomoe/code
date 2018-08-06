#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

const int inf = 0x3f3f3f3f;

int n, m, s, t, head[N], rest[N], to[N], f[N], dis[N], tot = 1;

void add(int u, int v, int ff) {
    to[++ tot] = v, f[tot] = ff, rest[tot] = head[u], head[u] = tot;
}

int bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    q.push(s);
    dis[s] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(f[i] && !~dis[v]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dis[t];
}

int dfs(int u, int flow) {
    if(u == t) return flow;
    int res = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(f[i] && dis[u] + 1 == dis[v]) {
            int a = dfs(v, min(flow, f[i]));
            flow -= a, f[i] -= a;
            f[i ^ 1] += a;
            res += a;
            if(!flow) break;
        }
    }
    if(!res) dis[u] = -1;
    return res;
}

int dinic() {
    int res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}

int b[N];

int main() {
    scanf("%d%d", &n, &m);
    s = n + m + 1, t = s + 1;
    int sum = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &b[i]);
        add(n + i, t, b[i]), add(t, n + i, 0);
    }
    for(int i = 1, a, k ; i <= n ; ++ i) {
        scanf("%d%d", &a, &k);
        for(int j = 1, x ; j <= k ; ++ j) {
            scanf("%d", &x);
            add(i, n + x, inf), add(n + x, i, 0);
        }
        add(s, i, a), add(i, s, 0);
        sum += a;
    }
    printf("%d\n", sum - dinic());
}
