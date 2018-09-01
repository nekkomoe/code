#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10, inf = 0x3f3f3f3f;
int head[N], rest[N], to[N], f[N], S, T, cnt, ed = 1;
void _add(int u, int v, int f) { to[++ ed] = v, :: f[ed] = f, rest[ed] = head[u], head[u] = ed; }
void add(int u, int v, int f) { _add(u, v, f), _add(v, u, 0); }
 
int D, n, m, skill_id[N], thing_id[N], cur[N];
 
inline int read() {
   int x=0,f=1;char c=getchar();
   for(; c<'0'||'9'<c; c=getchar())if(c=='-')f=-1;
   for(; '0'<=c&&c<='9'; c=getchar())x=(x<<3)+(x<<1)+c-'0';
   return x*f;
}
 
struct P {
    int d[2], x[2], y[2], ch[2], id;
    P() {}
    P(int x, int y) { d[0] = x, d[1] = y; }
    void init() {
        x[0] = x[1] = d[0];
        y[0] = y[1] = d[1];
        ch[0] = ch[1] = 0;
    }
    int getdis(P b) {
        return abs(d[0] - b.d[0]) + abs(d[1] - b.d[1]);
    }
    void update(P p) {
        x[0] = min(x[0], p.x[0]);
        x[1] = max(x[1], p.x[1]);
        y[0] = min(y[0], p.y[0]);
        y[1] = max(y[1], p.y[1]);
    }
    pair<int, int> dis(P p) {
        int dis[4], tot = 0, mn, mx;
        for(int i = 0 ; i < 2 ; ++ i)
            for(int j = 0 ; j < 2 ; ++ j)
                dis[tot ++] = p.getdis(P(x[i], y[j]));
        mx = *max_element(dis, dis + tot);
        mn = *min_element(dis, dis + tot);
        tot = 0;
        if(x[0] <= p.d[0] && p.d[0] <= x[1]) {
            dis[tot ++] = abs(y[0] - p.d[1]);
            dis[tot ++] = abs(y[1] - p.d[1]);
        }
        if(y[0] <= p.d[1] && p.d[1] <= y[1]) {
            dis[tot ++] = abs(x[0] - p.d[0]);
            dis[tot ++] = abs(x[1] - p.d[0]);
        }
        if(x[0] <= p.d[0] && p.d[0] <= x[1] &&
           y[0] <= p.d[1] && p.d[1] <= y[1]) {
           dis[tot ++] = 0;
        }
        if(tot) mn = min(mn, *min_element(dis, dis + tot));
        return make_pair(mn, mx);
    }
} p[N];
bool operator < (P a, P b) { return a.d[D] < b.d[D]; }
 
namespace DINIC {
    int dis[N];
    int bfs() {
        for(int i = 1 ; i <= cnt ; ++ i) dis[i] = -1;
        queue<int> q;
        q.push(S);
        dis[S] = 1;
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i = head[u] ; i ; i = rest[i]) {
                int v = to[i];
                if(f[i] && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis[T] != -1;
    }
    int dfs(int u, int flow) {
        if(u == T || !flow) return flow;
        int use = 0;
        for(int &i = cur[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(f[i] && dis[v] == dis[u] + 1) {
                int a = dfs(v, min(f[i], flow - use));
                f[i] -= a;
                f[i ^ 1] += a;
                use += a;
                if(use == flow) break;
            }
        }
        if(!use) dis[u] = -1;
        return use;
    }
    int sol() {
        int res = 0;
        while(bfs()) {
            for(int i = 1 ; i <= cnt ; ++ i) cur[i] = head[i];
            res += dfs(S, inf);
        }
        return res;
    }
}
 
namespace KDT {
    int root, id[N], pos[N];
    int build(int l, int r, int d) {
        D = d;
        int mid = (l + r) >> 1;
        nth_element(p + l, p + mid, p + r + 1);
        p[mid].init();
         
        id[mid] = ++ cnt;
        pos[mid] = ++ cnt, thing_id[cnt] = p[mid].id;
        add(id[mid], pos[mid], inf);
        add(pos[mid], T, 1);
         
        if(l <= mid - 1) {
            p[mid].ch[0] = build(l, mid - 1, d ^ 1);
            p[mid].update(p[p[mid].ch[0]]);
            add(id[mid], id[p[mid].ch[0]], inf);
        }
         
        if(mid + 1 <= r) {
            p[mid].ch[1] = build(mid + 1, r, d ^ 1);
            p[mid].update(p[p[mid].ch[1]]);
            add(id[mid], id[p[mid].ch[1]], inf);
        }
        return mid;
    }
    inline void met_build() {
        root = build(1, n, 0);
    }
     
    void dfs(int u, int ID, P o, int w) {
        if(!u) return ;
        if(p[u].getdis(o) <= w) add(ID, pos[u], 1);
        pair<int, int> dis = p[u].dis(o);
        int mndis = dis.first, mxdis = dis.second;
        if(mndis > w)
            return ;
        else if(mxdis <= w)
            add(ID, id[u], 1);
        else
            dfs(p[u].ch[0], ID, o, w),
            dfs(p[u].ch[1], ID, o, w);
    }
    void met_link(int x, int y, int w, int skid) {
        int id = ++ cnt;
        skill_id[cnt] = skid;
        add(S, id, 1);
        dfs(root, id, P(x, y), w);
    }
}
int getthing(int u) {
    if(thing_id[u]) return thing_id[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!(i & 1) && f[i ^ 1]) return -- f[i ^ 1], getthing(v);
    }
    assert(0);
    return -1;
}
int main() {
    n = read(), m = read(); 
    S = ++ cnt, T = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) p[i].d[0] = read(), p[i].d[1] = read(), p[i].id = i;
    KDT :: met_build();
    for(int i = 1, x, y, w ; i <= m ; ++ i) {
        x = read(), y = read(), w = read();
        KDT :: met_link(x, y, w, i);
    }
    printf("%d\n", DINIC :: sol());
    for(int i = head[S] ; i ; i = rest[i]) {
        int v = to[i];
        if(!(i & 1) && f[i ^ 1]) {
            printf("%d %d\n", getthing(v), skill_id[v]);
        }
    }
}
