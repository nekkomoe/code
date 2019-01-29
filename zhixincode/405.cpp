#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 10;

int n, m;

int head[N], flow[N], rest[N], to[N], tot, cnt, s, t;

void clear() {
    tot = 1;
    for(int i = 1 ; i <= cnt ; ++ i) head[i] = 0;
}

void add_sig(int u, int v, int f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int f) {
    add_sig(u, v, f), add_sig(v, u, 0);
}

int dis[N];
int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    dis[s] = 1, q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
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
const int inf = 0x3f3f3f3f;
int dfs(int u, int f) {
    if(u == t || !f) return f;
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(flow[i], f - use));
            flow[i] -= a, flow[i ^ 1] += a, use += a;
            if(use == f) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}
int getmx() {
    int res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}

struct E {
    int u, v;
} e[N];

int check(int T) {
    cnt = n + 2;
    s = n + 1, t = n + 2;
    clear();
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v;
        if(u < T && v >= T) {
            add(u, v, 1);
        }
    }
    for(int i = 1 ; i < T ; ++ i) {
        add(s, i, 1);
    }
    for(int i = T ; i <= n ; ++ i) {
        add(i, t, 1);
    }
    return getmx() == T - 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &e[i].u, &e[i].v);
        ++ e[i].u, ++ e[i].v;
        if(e[i].u > e[i].v) swap(e[i].u, e[i].v);
    }
    int l = 1, r = n, ans = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans - 1);
}
