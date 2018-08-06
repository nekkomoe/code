#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

const int inf = 0x3f3f3f3f;

int s, t, head[N], rest[N], flow[N], to[N], tot = 1, dis[N];

void add(int u, int v, int f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
}

int bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    dis[s] = 1, q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && !~dis[v]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dis[t];
}

int dfs(int u, int f) {
    if(u == t) return f;
    int res = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(f - res, flow[i]));
            flow[i] -= a, flow[i ^ 1] += a, res += a;
            if(res == f) break;
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

int res, mv[5][2] = { {0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1} }, n, m;

int p(int i, int j) {
    return (i - 1) * m + j;
}

int main() {
    scanf("%d%d", &n, &m), s = N - 10, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1, x ; j <= m ; ++ j) {
            scanf("%d", &x);
            ins(s, p(i, j), x);
            res += x;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1, x ; j <= m ; ++ j) {
            scanf("%d", &x);
            ins(p(i, j), t, x);
            res += x;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1, x ; j <= m ; ++ j) {
            scanf("%d", &x);
            ins(s, p(i, j) + n * m, x);
            res += x;
            for(int k = 0 ; k <= 4 ; ++ k) {
                int ii = i + mv[k][0], jj = j + mv[k][1];
                if(1 <= ii && ii <= n && 1 <= jj && jj <= m) {
                    ins(p(i, j) + n * m, p(ii, jj), inf);
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1, x ; j <= m ; ++ j) {
            scanf("%d", &x);
            ins(p(i, j) + n * m * 2, t, x);
            res += x;
            for(int k = 0 ; k <= 4 ; ++ k) {
                int ii = i + mv[k][0], jj = j + mv[k][1];
                if(1 <= ii && ii <= n && 1 <= jj && jj <= m) {
                    ins(p(ii, jj), p(i, j) + n * m * 2, inf);
                }
            }
        }
    }
    printf("%d\n", res - dinic());
}
