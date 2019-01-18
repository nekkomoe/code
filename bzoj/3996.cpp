// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 5e6 + 10;

int b[510][510], c[510];

int head[N], rest[N], to[N], flow[N], tot = 1;

void ins(int u, int v, int w) {
    to[++ tot] = v, flow[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w) {
    ins(u, v, w), ins(v, u, 0);
}

int dis[N], s, t, cnt;

int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) dis[i] = -1;
    dis[s] = 1; queue<int> q; q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == -1 && flow[i]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int u, int f) {
    int use = 0;
    if(u == t || !f) return f;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(dis[v] == dis[u] + 1 && flow[i]) {
            int a = dfs(v, min(flow[i], f - use));
            flow[i] -= a, flow[i ^ 1] += a, use += a;
            if(use == f) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}

const int inf = 0x3f3f3f3f;

int sol() {
    int res = 0;
    while(bfs()) {
        res += dfs(s, inf);
    }
    return res;
}
int n, idA[510], idB[510][510], idC[510];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            scanf("%d", &b[i][j]);
    for(int i = 1 ; i <= n ; ++ i)
        scanf("%d", &c[i]);
    for(int i = 1 ; i <= n ; ++ i) idA[i] = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            idB[i][j] = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) idC[i] = ++ cnt;
    s = ++ cnt, t = ++ cnt;
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            ans += b[i][j];
            add(s, idB[i][j], b[i][j]);
            add(idB[i][j], idA[i], inf);
            add(idB[i][j], idA[j], inf);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        add(idA[i], idC[i], inf);
        add(idC[i], t, c[i]);
    }

    printf("%d\n", ans - sol());
}

