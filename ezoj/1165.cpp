#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

template<typename T> inline void read(T &x) {
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 1e7 + 10;

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
    fill(dis + 1, dis + 1 + t, -1);
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

signed main() {
    int sum = 0;
    read(n), read(m), s = n + 2 * m + 1, t = s + 1;
    for(int i = 1, ap, ad ; i <= n ; ++ i) {
        read(ap), read(ad);
        ins(s, i, ap), ins(i, t, ad);
        sum += ap + ad;
    }
    for(int i = 1, u, v, AD, AP, Ahr ; i <= m ; ++ i) {
        read(u), read(v), read(AD), read(AP), read(Ahr);
        int x = n + i, y = n + m + i;
        ins(s, x, AP), ins(y, t, AD);
        ins(x, u, AP), ins(x, v, AP);
        ins(u, y, AD), ins(v, y, AD);
        ins(u, v, Ahr), ins(v, u, Ahr);
        sum += AP + AD;
    }
    printf("%lld\n", sum - dinic());
}

