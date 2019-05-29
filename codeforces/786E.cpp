#include <bits/stdc++.h>
using namespace std;
const int IN = 2e4 + 10, N = 5e6 + 10, inf = 0x3f3f3f3f;

vector<int> g[IN];
int fa[IN][16], dep[IN];
int n, m;

int head[N], rest[N], to[N], flow[N], cur[N], tot = 1;
void add_sub(int u, int v, int w) {
    to[++ tot] = v, flow[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w) {
    if(!v) {
        return ;
    }
    // printf("%d -> %d, %d\n", u, v, w);
    add_sub(u, v, w), add_sub(v, u, 0);
}
int S, T, cnt, dis[N];
int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    queue<int> q;
    q.push(S), dis[S] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[T] != -1;
}
int dfs(int u, int f) {
    if(u == T) {
        return f;
    }
    int use = 0;
    for(int &i = cur[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(flow[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(f - use, flow[i]));
            flow[i] -= a, flow[i ^ 1] += a, use += a;
            if(use == f) {
                break;
            }
        }
    }
    if(!use) {
        dis[u] = -1;
    }
    return use;
}
int getmxflow() {
    int res = 0;
    while(bfs()) {
        
        // printf("res = %d, %d, %d\n", res, dis[T], cnt);

        for(int i = 1 ; i <= cnt ; ++ i) {
            cur[i] = head[i];
        }
        res += dfs(S, inf);
    }
    return res;
}

int pos[IN][16];
pair<int, int> rev[N];
map<pair<int, int>, int> ids;

void go(int u) {
    dep[u] = dep[fa[u][0]] + 1;

    if(fa[u][0]) {
        for(int i = 0 ; i <= 15 ; ++ i) {
            pos[u][i] = ++ cnt;
        }
        add(pos[u][0], T, 1);

        int a = fa[u][0], b = u; if(a > b) swap(a, b);
        rev[pos[u][0]] = make_pair(a, b);
        // printf("set ed: %d\n", pos[u][0]);

        for(int i = 1 ; i <= 15 ; ++ i) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            add(pos[u][i], pos[u][i - 1], inf);
            add(pos[u][i], pos[fa[u][i - 1]][i - 1], inf);
        }
    }
    for(int v: g[u]) {
        if(v != fa[u][0]) {
            fa[v][0] = u;
            go(v);
        }
    }
}

void getlca(int u, int v, int x) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 15 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            add(x, pos[u][i], inf);
            u = fa[u][i];
        }
    }
    if(u == v) {
        return ;
    }
    for(int i = 15 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            add(x, pos[u][i], inf);
            add(x, pos[v][i], inf);
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    add(x, pos[u][0], inf);
    add(x, pos[v][0], inf);
}

int idsman[N];

int main() {
    S = ++ cnt, T = ++ cnt;
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        if(u > v) swap(u, v);
        ids[make_pair(u, v)] = i;
        g[u].push_back(v), g[v].push_back(u);
    }
    go(1);
    for(int i = 1 ; i <= m ; ++ i) {
        int x = ++ cnt;
        idsman[x] = i;
        add(S, x, 1);
        int u, v; scanf("%d%d", &u, &v);
        getlca(u, v, x);
    }
    printf("%d\n", getmxflow());
    vector<int> vis(cnt + 10), man(cnt + 10), guard(cnt + 10);

    int rman = m, rg = 0;

    queue<int> q;
    q.push(S);
    while(q.size()) {
        int u = q.front(); q.pop();
        vis[u] = 1;

        // printf("u = %d\n", u);

        if(idsman[u]) {
            // puts("A");
            man[idsman[u]] = 1;
            -- rman;
        }

        if(rev[u].first) {
            // puts("B");
            guard[ids[rev[u]]] = 1;
            ++ rg;
        }

        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && !vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    printf("%d ", rman);
    for(int i = 1 ; i <= m ; ++ i) {
        if(!man[i]) {
            printf("%d ", i);
        }
    }
    puts("");
    
    printf("%d ", rg);
    for(int i = 1 ; i < n ; ++ i) {
        if(guard[i]) {
            printf("%d ", i);
        }
    }
    puts("");
}
