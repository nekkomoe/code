#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

const int inf = 1000000000;

int n, m, s, t, head[N], rest[N], to[N], flow[N], dis[N], tot = 1;

void add(int u, int v, int f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
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

int p, q, r, d, v[50][50][50], mv[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int P(int x, int y, int z) {
    return z ? (z - 1) * p * q + (x - 1) * q + y : 0;
} 

int main() {
    scanf("%d%d%d%d", &p, &q, &r, &d);
    t = p * q * r + 1;
    for(int i = 1 ; i <= r ; ++ i) {
        for(int j = 1 ; j <= p ; ++ j) {
            for(int k = 1 ; k <= q ; ++ k) {
                scanf("%d", &v[j][k][i]);
            }
        }
    }
    for(int i = 1 ; i <= p ; ++ i) {
        for(int j = 1 ; j <= q ; ++ j) {
            for(int k = 1 ; k <= r ; ++ k) {
                ins(P(i, j, k - 1), P(i, j, k), v[i][j][k]);
                if(k > d) {
                    for(int l = 0 ; l < 4 ; ++ l) {
                        int ii = i + mv[l][0], jj = j + mv[l][1];
                        if(1 <= ii && ii <= p && 1 <= jj && jj <= q) {
                            ins(P(i, j, k), P(ii, jj, k - d), inf);
                        }
                    }
                }
            }
            ins(P(i, j, r), t, inf);
        }
    }
    printf("%d\n", dinic());
}