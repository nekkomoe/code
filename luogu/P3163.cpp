// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10, inf = 0x3f3f3f3f;

int head[N], rest[N], to[N], w[N], tot, n, S, T, dis[N], a1, a2, an, b1, b2, bn;
char str[2010][2010];

void add(int u, int v, int c) {
    to[++ tot] = v, w[tot] = c, rest[tot] = head[u], head[u] = tot;
}

int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= n + 2 ; ++ i) dis[i] = -1;
    dis[S] = 1, q.push(S);
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
    return dis[T] != -1;
}

int dfs(int u, int f) {
    if(u == T || !f) return f;
    int res = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(w[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(f - res, w[i]));
            w[i] -= a, w[i ^ 1] += a, res += a;
        }
    }
    if(!res) dis[u] = -1;
    return res;
}

void init() {
    tot = 1;
    for(int i = 1 ; i <= n + 2 ; ++ i) {
        head[i] = 0;
    }
}

int sol() {
    init();
    S = n + 1, T = n + 2;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            if(str[i][j] != 'X') {
                add(i, j, str[i][j] == 'O' ? 2 : inf);
                add(j, i, 0);
            }
        }
    }
    add(S, a1, an), add(a1, S, 0);
    add(a2, T, an), add(T, a2, 0);
    add(S, b1, bn), add(b1, S, 0);
    add(b2, T, bn), add(T, b2, 0);
    int res = 0;
    while(bfs()) res += dfs(S, inf);
    return res == an + bn;
}

int main() {
    while(scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != -1) {
        ++ a1, ++ a2, ++ b1, ++ b2, an *= 2, bn *= 2;
        for(int i = 1 ; i <= n ; ++ i) {
            scanf("%s", str[i] + 1);
        }
        puts(sol() && (swap(b1, b2), sol()) ? "Yes" : "No");
    }
}
