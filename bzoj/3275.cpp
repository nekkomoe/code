#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 10;

const int inf = 1000000000;

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

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int sum, a[N];

int main() {
    scanf("%d", &n), s = N - 10, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]), sum += a[i];
        if(a[i] & 1) ins(i, t, a[i]); else ins(s, i, a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] & 1) continue;
        for(int j = 1 ; j <= n ; ++ j) {
            if(a[j] & 1) {
                int t = round(sqrt(a[i] * a[i] + a[j] * a[j]));
                if(gcd(a[i], a[j]) == 1 && a[i] * a[i] + a[j] * a[j] == t * t) ins(i, j, inf);
            }
        }
    }
    printf("%d\n", sum - dinic());
}
