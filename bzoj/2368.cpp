#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
 
namespace NetFlow {
    int S, T;
    int flow[N], head[N], rest[N], to[N], tot, dis[N];
 
    void clear(int cnt) {
        S = ++ cnt, T = ++ cnt;
        tot = 1;
        for(int i = 1 ; i <= cnt ; ++ i) head[i] = 0;
    }
 
    void add_sig(int u, int v, int w) {
        to[++ tot] = v, flow[tot] = w, rest[tot] = head[u], head[u] = tot;
    }
    void add(int u, int v, int w) {
        add_sig(u, v, w), add_sig(v, u, 0);
    }
 
    int bfs() {
        queue<int> q;
        for(int i = 1 ; i <= T ; ++ i) dis[i] = -1;
        q.push(S), dis[S] = 1;
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
        return dis[T] != -1;
    }
 
    int dfs(int u, int f) {
        if(u == T || !f) return f;
        int use = 0;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == dis[u] + 1 && flow[i]) {
                int a = dfs(v, min(flow[i], f - use));
                use += a, flow[i] -= a, flow[i ^ 1] += a;
                if(use == f) break;
            }
        }
        if(!use) dis[u] = -1;
        return use;
    }
 
    int sol() {
        int res = 0;
        while(bfs()) res += dfs(S, 0x3f3f3f3f);
        return res;
    }
}
 
struct Tree {
    int head[N], rest[N], to[N], tot;
    void add(int u, int v) {
        to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
    }
    void clear(int n) {
        for(int i = 1 ; i <= n ; ++ i) head[i] = 0;
        tot = 0;
    }
} Tx, Ty;
 
 
int n, m, mat[210][210], Qx[N], Qy[N], Px, Py;
 
int dfs(int x, int y, int fa_x, int fa_y) {
    if(mat[x][y]) return mat[x][y] == 1;
 
    for(int i = Tx.head[x] ; i ; i = Tx.rest[i]) {
        int Vx = Tx.to[i];
        if(Vx != fa_x) {
            for(int j = Ty.head[y] ; j ; j = Ty.rest[j]) {
                int Vy = Ty.to[j];
                if(Vy != fa_y) {
                    dfs(Vx, Vy, x, y);
                }
            }
        }
    }
 
    Px = Py = 0;
 
    for(int i = Tx.head[x] ; i ; i = Tx.rest[i]) {
        int v = Tx.to[i];
        if(v != fa_x) {
            Qx[++ Px] = v;
        }
    }
 
    for(int i = Ty.head[y] ; i ; i = Ty.rest[i]) {
        int v = Ty.to[i];
        if(v != fa_y) {
            Qy[++ Py] = v;
        }
    }
     
    NetFlow :: clear(Px + Py);
    for(int i = 1 ; i <= Px ; ++ i) {
        NetFlow :: add(NetFlow :: S, i, 1);
    }
    for(int i = 1 ; i <= Py ; ++ i) {
        NetFlow :: add(Px + i, NetFlow :: T, 1);
    }
 
    for(int i = 1 ; i <= Px ; ++ i) {
        for(int j = 1 ; j <= Py ; ++ j) {
            int u = Qx[i], v = Qy[j];
            if(mat[u][v] == 1) {
                NetFlow :: add(i, Px + j, 1);
            }
        }
    }
    if(NetFlow :: sol() == Py)
        mat[x][y] = 1;
    else
        mat[x][y] = -1;
    return mat[x][y] == 1;
}
 
void sol() {
    scanf("%d", &n);
    Tx.clear(n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        Tx.add(u, v);
        Tx.add(v, u);
    }
    scanf("%d", &m);
    Ty.clear(m);
    for(int i = 1, u, v ; i < m ; ++ i) {
        scanf("%d%d", &u, &v);
        Ty.add(u, v);
        Ty.add(v, u);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int x = 1 ; x <= n ; ++ x)
            for(int y = 1 ; y <= n ; ++ y)
                mat[x][y] = 0;
        if(dfs(i, 1, 0, 0)) {
            puts("YES");
            return ;
        }
    }
    puts("NO");
}
 
int main() {
    int T; scanf("%d", &T);
    while(T --) sol();
}
