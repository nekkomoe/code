// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;

const int N = 5010, E = 2e6 + 10;
vector<int> g[N];
int dis[N][N], n, m, q, ed[E][2], a[N], fa[N][2];
int head[E], rest[E], to[E], tot;
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
queue<pair<int, int> > que;

void getans() {
    while(que.size()) {
        int u = que.front().first, v = que.front().second;
        que.pop();
        if(dis[u][v]) continue;
        dis[u][v] = dis[v][u] = 1;
        for(int x: g[u]) {
            for(int y: g[v]) {
                if(a[x] == a[y] && !dis[x][y]) {
                    que.push(make_pair(x, y));
                }
            }
        }
    }
}


int col[N], ban[N];
void dfs(int u, int c) {
    col[u] = c;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!col[v]) {
            dfs(v, -c);
        } else if(col[v] == c) {
            ban[abs(c)] = 1;
        }
    }
}
int getfa(int x, int y) {
    return x == fa[x][y] ? x : fa[x][y] = getfa(fa[x][y], y);
}

char str[E];
int main() {
    scanf("%d%d%d", &n, &m, &q);
    scanf("%s", str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = str[i] - '0';
        fa[i][0] = fa[i][1] = i;
        que.push(make_pair(i, i));
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &ed[i][0], &ed[i][1]);
        int u = ed[i][0], v = ed[i][1];
        if(a[u] == a[v]) {
            add(u, v), add(v, u);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!col[i]) {
            dfs(i, i);
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u = ed[i][0], v = ed[i][1];
        if(a[u] == a[v]) {
            if(getfa(u, 0) != getfa(v, 0)) {
                g[u].push_back(v);
                g[v].push_back(u);
                fa[getfa(u, 0)][0] = getfa(v, 0);
                que.push(make_pair(u, v));
            }
        } else {
            if(getfa(u, 1) != getfa(v, 1)) {
                g[u].push_back(v);
                g[v].push_back(u);
                fa[getfa(u, 1)][1] = getfa(v, 1);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(col[i] == i && ban[i]) {
            g[i].push_back(i);
        }
    }
    getans();
    while(q --) {
        int u, v; scanf("%d%d", &u, &v);
        puts(dis[u][v] ? "YES" : "NO");
    }
}
