#include <bits/stdc++.h>
using namespace std;
const int N = 2000 + 10;
int mat[N], n;
int a[N][N], T, vis[N], ans;

int tmp[N][N], mx;
int dfs(int u) {
    for(int v = 1 ; v <= mx ; ++ v) {
        if(a[u][v] && vis[v] != T) {
            vis[v] = T;
            if(!mat[v] || dfs(mat[v])) {
                mat[v] = u;
                return 1;
            }
        }
    }
    return 0;
}


namespace MAXFLOW {
    const int N = 2e5 + 10, M = 2e5 + 10, inf = 0x3f3f3f3f;
    int head[N], rest[M], to[M], w[M], tot = 1;
    
    void add(int u, int v, int wi) {
        to[++ tot] = v, w[tot] = wi, rest[tot] = head[u], head[u] = tot;
    }
    void lk(int u, int v, int w) {
        add(u, v, w), add(v, u, 0);
    }
    
    int s, t;
    
    int dis[N];
    
    bool bfs() {
        for(int i = 1 ; i <= t ; ++ i) dis[i] = -1;
        dis[s] = 1;
        queue<int> q; q.push(s);
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int i = head[u] ; i ; i = rest[i]) {
                int v = to[i];
                if(w[i] && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis[t] != -1;
    }
    
    int cur[N];
    int dfs(int u, int flow) {
        int use = 0;
        if(u == t || !flow) return flow;
        for(int &i = cur[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == dis[u] + 1) {
                int a = dfs(v, min(flow - use, w[i]));
                use += a;
                w[i] -= a;
                w[i ^ 1] += a;
                if(use == flow) break;
            }
        }
        if(!use) dis[u] = -1;
        return use;
    }
    
    int getmaxflow() {
        int ans = 0;
        while(bfs()) {
            for(int i = 1 ; i <= t ; ++ i) cur[i] = head[i];
            ans += dfs(s, inf);
        }
        return ans;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &tmp[i][0]);
        for(int j = 1 ; j <= tmp[i][0] ; ++ j) {
            scanf("%d", &tmp[i][j]);
            mx = max(mx, tmp[i][j]);
            a[i][tmp[i][j]] = 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) ++ T, dfs(i);
    MAXFLOW :: s = n + mx + 1;
    MAXFLOW :: t = MAXFLOW :: s + 1;
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= mx ; ++ j)
            if(a[i][j] && i != mat[j])
                MAXFLOW :: lk(i, mat[j], 0x3f3f3f3f);
    for(int i = 1 ; i <= n ; ++ i) {
        int val; scanf("%d", &val); val = -val;
        if(val < 0) {
            MAXFLOW :: lk(i, MAXFLOW :: t, -val);
        } else {
            ans += val;
            MAXFLOW :: lk(MAXFLOW :: s, i, val);
        }
    }
    ans -= MAXFLOW :: getmaxflow();
    printf("%d\n", ans > 0 ? -ans : 0);
}

