#include "bits/stdc++.h"
using namespace std;
typedef double ld;
const ld eps = 1e-6;
const int N = 1e6 + 10;
int n, m, k;
vector<pair<int, int> > g[60];
vector<int> rel[510];

ld f[60];
int vis[60];
int top;
pair<int, int> ed[510];
ld y[N];

int head[N], rest[N], to[N], tot;
ld flow[N];
void ins(int u, int v, ld c) {
    to[++ tot] = v, flow[tot] = c, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, ld c) {
    ins(u, v, c), ins(v, u, 0);
}
int dis[N], S, T;
int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= T ; ++ i) dis[i] = -1;
    dis[S] = 1, q.push(S);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] < eps || dis[v] != -1) continue;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
    return dis[T] != -1;
}
int cur[N];
ld dfs(int u, ld f) {
    if(u == T || f < eps) return f;
    ld use = 0;
    for(int &i = cur[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] < eps || dis[v] != dis[u] + 1) continue;
        ld a = dfs(v, min(f - use, flow[i]));
        flow[i] -= a;
        flow[i ^ 1] += a;
        use += a;
        if(fabs(f - use) < eps) {
            break;
        }
    }
    if(use < eps) {
        dis[u] = -1;
    }
    return use;
}

int bel[N];
int check(ld k) {
    tot = 1;
    S = top + 1, T = S + 1;
    for(int i = 1 ; i <= T ; ++ i) head[i] = 0;

    ld res = 0;
    for(int i = 1 ; i <= top ; ++ i) {
        bel[ed[i].second] = i;
        y[i] = 1 + f[ed[i].first] - k;
        if(y[i] < 0) {
            add(i, T, -y[i]);
        } else {
            res += y[i];
            add(S, i, y[i]);
        }
    }
    
    for(int i = 1 ; i <= top ; ++ i) {
        int x = ed[i].second;
        for(int y: rel[x]) {
            int u = bel[x], v = bel[y];
            add(u, v, 1e9);
        }
    }
    
    while(bfs()) {
        for(int i = 1 ; i <= T ; ++ i) {
            cur[i] = head[i];
        }
        res -= dfs(S, 1e9);
    }
    return res > 0;
}

void dfs(int u) {
    if(vis[u] || g[u].empty()) return;
    for(auto t: g[u]) {
        dfs(t.first);
    }
    vis[u] = 1;
    top = 0;
    for(auto t: g[u]) {    
        ed[++ top] = t;
    }
    ld l = 0, r = n;
    for(int _ = 10 ; _ -- ; ) {
        ld mid = (l + r) / 2;
        if(check(mid)) { // >= mid
            l = mid;
        } else {
            r = mid;
        }
    }
    f[u] = l;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(make_pair(v, i));
    }
    for(int i = 1 ; i <= k ; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        rel[x].push_back(y); 
    }
    for(int i = 1 ; i <= m ; ++ i) {
        sort(rel[i].begin(), rel[i].end());
        rel[i].erase(unique(rel[i].begin(), rel[i].end()), rel[i].end());
    }
    dfs(1);
    cout << fixed << setprecision(10) << f[1] << endl;
}
