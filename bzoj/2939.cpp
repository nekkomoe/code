#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define int ll

const int N = 5e6 + 10;

const int inf = 21474836400000ll;

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

int a[N], sum;

signed main() {
    scanf("%lld", &n), s = n + 1, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) {
        int cnt = 0;
        ins(s, i, a[i]);
        for(int j = 1, x ; j <= n ; ++ j) {
            scanf("%d", &x);
            cnt += x, sum += x;
            ins(i, j, x * 2);
        }
        ins(i, t, cnt);
    }
    printf("%lld\n", sum - dinic());
}