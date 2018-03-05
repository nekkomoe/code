#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

const int inf = 0x3f3f3f3f;

int n, m, s, t, head[N], rest[N], to[N], f[N], dis[N], tot = 1;

void add(int u, int v, int ff) {
    to[++ tot] = v, f[tot] = ff, rest[tot] = head[u], head[u] = tot;
}

void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
}

int bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    q.push(s);
    dis[s] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(f[i] && !~dis[v]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dis[t];
}

int dfs(int u, int flow) {
    if(u == t) return flow;
    int res = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(f[i] && dis[u] + 1 == dis[v]) {
            int a = dfs(v, min(flow, f[i]));
            flow -= a, f[i] -= a;
            f[i ^ 1] += a;
            res += a;
            if(!flow) break;
        }
    }
    if(!res) dis[u] = -1;
    return res;
}

int dinic() {
    int res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}

char mp[100][100];

int k;

int check(int a) {
    memset(head, 0, sizeof head), tot = 1, memset(f, 0, sizeof f);
    s = 4 * n + 1, t = s + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        ins(s, i, a);
        ins(3 * n + i, t, a);
        ins(i, n + i, k);
        ins(n * 2 + i, n * 3 + i, k);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(mp[i][j] == 'Y') {
                ins(i, n * 3 + j, 1);
            } else {
                ins(n + i, n * 2 + j, 1);
            }
        }
    }
    return a * n <= dinic();
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%s", mp[i] + 1);
    for(int i = n ; i >= 0 ; -- i) {
        if(check(i)) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("0");
}
