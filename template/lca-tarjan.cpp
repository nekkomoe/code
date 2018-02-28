#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 1000010;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}

int fa[N];

int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}

int n, m, s;

struct Q {
    int v, id;
};

vector<Q> ask[N];

int ans[N], vis[N];

void dfs(int u,int f) {
    vis[u] = 1;
    for(int i = 0 ; i < ask[u].size() ; ++ i) {
        if(vis[ask[u][i].v]) {
            ans[ask[u][i].id] = get(ask[u][i].v);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != f) {
            dfs(v, u);
            fa[get(v)] = u;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &s);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v ,u);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        fa[i] = i;
    }
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        ask[u].push_back((Q) {v, i});
        ask[v].push_back((Q) {u, i});
    }
    dfs(s, 0);
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
