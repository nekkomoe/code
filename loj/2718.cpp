// luogu-judger-enable-o2
%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, M = 4e5 + 10;
struct E { int u, v, w, a; } e[M];
bool operator < (E a, E b) { return a.a > b.a; }
int head[N], rest[M * 2], to[M * 2], w[M * 2], tot;
inline void add(int u, int v, int w, int a) { to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot; }
int n, m;
int dis[N];
bool vis[N];
struct T { int u, dis; };
bool operator < (T a, T b) { return a.dis > b.dis; }
priority_queue<T> pq;
int fa[N + M][21], mn[N + M];
int tp[N + M];
int get(int x) { return x == tp[x] ? x : tp[x] = get(tp[x]); }
int treemn[N + M], lc[N + M], rc[N + M], dep[N + M];
int deg[N + M];
inline void read(int &x) {
    char c = x = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}
int que[(N + M) * 10];

int fk[N + M];

void bfs(int rt) {
    int l, r;
    que[l = r = 1] = rt;
    while(l <= r) {
        int u = que[l ++];
        // cout << u << ' ' << lc[u] << ' ' << rc[u] << endl;
        // cout << fk[u] << endl;
        // fk[u] = 1;
        int f = fa[u][0];
        dep[u] = dep[f] + 1;
        if(lc[u]) {
            que[++ r] = lc[u];
            // cout << lc[u] << " <- " << u << endl;
        }
        if(rc[u]) {
            que[++ r] = rc[u];
            // cout << rc[u] << " <- " << u << endl;
        }
        // cout << l << ' ' << r << endl;
    }

    // exit(0);

    l = 1, r = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        que[++ r] = i;
        treemn[i] = dis[i];
    }
    while(l <= r) {
        int u = que[l ++];
        int f = fa[u][0];
        if(f && ! -- deg[f]) que[++ r] = f;
        treemn[f] = min(treemn[f], treemn[u]);
    }
}
void sol() {
    read(n), read(m);
    tot = 0;
    for(int i = 1 ; i <= n ; ++ i) head[i] = vis[i] = 0, dis[i] = 2e9 + 10;
    for(int i = 1 ; i <= m ; ++ i)
        read(e[i].u), read(e[i].v), read(e[i].w), read(e[i].a),
        add(e[i].u, e[i].v, e[i].w, e[i].a),
        add(e[i].v, e[i].u, e[i].w, e[i].a);
    dis[1] = 0;
    pq.push((T) { 1, 0 });
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] > (ll) dis[u] + w[i]) {
                dis[v] = dis[u] + w[i];
                pq.push((T) { v, dis[v] });
            }
        }
    }
    int q, k, s; read(q), read(k), read(s);
    for(int i = 1 ; i <= n ; ++ i) {
        tp[i] = i, mn[i] = s + 10;
        lc[i] = rc[i] = deg[i] = 0;
    }
    sort(e + 1, e + 1 + m);
    int rt = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int id = n + i;
        int u = get(e[i].u), v = get(e[i].v);
        if(u == v) continue;
        rt = id;
        tp[id] = id, fa[id][0] = 0, deg[id] = 2;
        tp[u] = id, tp[v] = id, lc[id] = u, rc[id] = v;
        fa[u][0] = id, fa[v][0] = id;
        mn[id] = e[i].a;
        treemn[id] = 2e9 + 10;
    }

    // for(int i = 1 ; i <= n ; ++ i) cout << lc[i] << ' ' << rc[i] << endl;
    // exit(0);
    

    for(int j = 1 ; j <= 20 ; ++ j)
        for(int i = 1 ; i <= n + m ; ++ i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];

    bfs(rt);


    for(int i = 1, lastans = 0, v0, p0, v, p ; i <= q ; ++ i) {
        read(v0), read(p0);
        v = (v0 + k * lastans - 1) % n + 1;
        p = (p0 + k * lastans) % (s + 1);
        lastans = dis[v];
        for(int i = 20 ; ~ i ; -- i) {
            if(dep[fa[v][i]] >= dep[rt] && mn[fa[v][i]] > p) {
                lastans = min(lastans, treemn[fa[v][i]]);
                v = fa[v][i];
            }
        }
        printf("%d\n", lastans);
    }
}
int main() {
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);
    int T; read(T);
    while(T --) sol();
}
