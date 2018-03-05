%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

const int inf = 1e9;

int n, m, s, t, head[N], rest[N], to[N], flow[N], dis[N], tot = 1, mv[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

void add(int u, int v, int f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
}

void ins2(int u, int v, int f) {
    ins(u, v, f), ins(v, u, f);
}

bool bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    dis[s] = 0;
    q.push(s);
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int u, int f) {
    if(u == t) return f;
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!flow[i] || dis[v] != dis[u] + 1) continue;
        int a = dfs(v, min(f - use, flow[i]));
        use += a, flow[i] -= a, flow[i ^ 1] += a;
        if(use == f) break;
    }
    if(!use) dis[u] = -1;
    return use;
}

int dinic() {
    int res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}

int p[N], sum;

int main() {
    scanf("%d%d", &n, &m);
    s = N - 10, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &p[i]);
        ins(m + i, t, p[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        ins(i, m + a, inf);
        ins(i, m + b, inf);
        ins(s, i, c);
        sum += c;
    }
    printf("%d\n", sum - dinic());
}
