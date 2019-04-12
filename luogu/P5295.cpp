// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

int n, m;
pair<int, int> ed[N];

int head[N], rest[N], to[N], tot, S, T, w[N], dis[N];
void ins(int u, int v, int c) {
    to[++ tot] = v, w[tot] = c, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int c) {
    ins(u, v, c), ins(v, u, 0);
}

int bfs() {
    queue<int> q;
    for(int i = 1 ; i <= T ; ++ i) dis[i] = -1;
    q.push(S), dis[S] = 1;
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
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(w[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(w[i], f - use));
            w[i] -= a, w[i ^ 1] += a, use += a;
            if(use == f) break;
        }
    }
    if(!use) dis[u] = -1;
    return use;
}
int getmxflow() {
    int res = 0;
    while(bfs()) {
        res += dfs(S, 0x3f3f3f3f);
    }
    return res;
}

int sol(int ban) {
    tot = 1;
    for(int i = 1 ; i <= T ; ++ i) head[i] = 0;
    S = n + m + 1, T = S + 1;
    int res = m - 2;
    for(int i = 1 ; i <= n ; ++ i) {
        if(i != ban) {
            add(i, T, 2);
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u = ed[i].first, v = ed[i].second;
        add(n + i, u, 0x3f3f3f3f);
        add(n + i, v, 0x3f3f3f3f);
        add(S, n + i, 1);
    }
    return res - getmxflow();
}

void runprog() {
    int ans = 0xcfcfcfcf;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &ed[i].first, &ed[i].second);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ans = max(ans, sol(i));
    }
    puts(ans + 2 > 0 ? "No" : "Yes");
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
