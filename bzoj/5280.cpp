// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m;
vector<int> g[N];
int head[N], rest[N * 2], to[N * 2], tot, vis[N], deg[N];
priority_queue<int, vector<int>, greater<int> > pq;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

bool check(int x, int ty = 0) {
    memset(head, 0, sizeof head);
    memset(vis, 0, sizeof vis);
    memset(deg, 0, sizeof deg);
    tot = 0;
    for(int i = 1 ; i <= x ; ++ i) {
        for(int j = 1 ; j < g[i].size() ; ++ j) {
            add(g[i][j - 1], g[i][j]);
            ++ deg[g[i][j]];
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!deg[i]) {
            pq.push(i);
            vis[i] = 1;
        }
    }
    while(pq.size()) {
        int u = pq.top(); pq.pop();
        if(ty) printf("%d ", u);
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(vis[v]) return 0;
            if(! -- deg[v]) pq.push(v), vis[v] = 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) if(!vis[i]) return 0;
    return 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int t, x; scanf("%d", &t);
        while(t --) scanf("%d", &x), g[i].push_back(x);
    }
    int l = 0, r = m, ans = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid, l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    check(ans, 1);
}
