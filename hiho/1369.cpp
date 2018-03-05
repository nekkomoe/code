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

int main() {
    scanf("%d%d", &n, &m), s = 1, t = n;
    for(int i = 1, u, v, f ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &f);
        add(u, v, f), add(v, u, 0);
    }
    printf("%d\n", dinic());
}
