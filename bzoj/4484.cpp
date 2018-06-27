#include "bits/stdc++.h"
using namespace std;
const int N = 30000 + 10, M = 100000 + 10;
bitset<N> in[N], out[N];
int n, m;
int head[N], rest[M], to[M], tot;
void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
vector<int> G[N];
int deg[N], d[N];

void topo() {
    queue<int> q;
    for(int i = 1 ; i <= n ; ++ i) if(!deg[i]) q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(!-- deg[v]) q.push(v);
            in[v].set(u);
            in[v] |= in[u];
        }
    }
}

void fafa() {
    queue<int> q;
    for(int i = 1 ; i <= n ; ++ i) if(!d[i]) q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < G[u].size() ; ++ i) {
            int v = G[u][i];
            if(!-- d[v]) q.push(v);
            out[v].set(u);
            out[v] |= out[u];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        ++ deg[v];
        G[v].push_back(u);
        ++ d[u];
    }
    topo();
    fafa();
    int ans = 0;
    for(int u = 1 ; u <= n ; ++ u) {
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if((in[v] & out[u]).count()) {
                ++ ans;
            }
        }
    }
    printf("%d\n", ans);
}
