#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

template<typename T> inline void read(T &x) {
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

const int N = 1e5 + 10;

int head[N], rest[N], to[N], tot = 1, f[N], mv[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

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

int id(int i, int j) {
    return (i - 1) * m + j;
}

signed main() {
    int sum = 0;
    scanf("%lld%lld", &n, &m), s = m * n + 1, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            int x; read(x);
            sum += x;
            if((i + j) & 1) {
                ins(s, id(i, j), x);
                for(int k = 0 ; k < 4 ; ++ k) {
                    int x = i + mv[k][0], y = j + mv[k][1];
                    if(1 <= x && x <= n && 1 <= y && y <= m) ins(id(i, j), id(x, y), 0x3f3f3f3f);
                }
            } else ins(id(i, j), t, x);
        }
    }
    printf("%lld\n", sum - dinic());
}

