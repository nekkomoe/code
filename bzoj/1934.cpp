#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T> inline void read(T &x) {
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 2e5 + 10;

int head[N], rest[N], to[N], tot = 1, f[N];

void add(int u, int v, int f) {
    to[++ tot] = v, :: f[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
}

int dis[N];

queue<int> q;

int n, m, s, t;

int bfs() {
    memset(dis, -1, sizeof dis);
    dis[s] = 0;
    q.push(s);
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

int dfs(int u, int f) {
    if(u == t) return f;
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(:: f[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(:: f[i], f - use));
            use += a, :: f[i] -= a, :: f[i ^ 1] += a;
            if(use == f) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}

int dinic() {
    int res = 0;
    while(bfs()) res += dfs(s, 0x3f3f3f3f);
    return res;
}

int main() {
    scanf("%d%d", &n, &m), s = n + 1, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        ins(s, i, x), ins(i, t, !x);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        ins(u, v, 1), ins(v, u, 1);
    }
    printf("%d\n", dinic());
}

