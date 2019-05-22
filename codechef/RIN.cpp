#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e6 + 10;
const int inf = 0x3f3f3f3f;

int n, m, k, X[110][110];

int ids[110][110];
ll ans;

int head[N], rest[N], to[N], tot = 1, w[N], cur[N];
void add_sig(int u, int v, int w) {
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, int w) {
    add_sig(u, v, w), add_sig(v, u, 0);
}
int dis[N], cnt, s, t;
int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    queue<int> q;
    q.push(s);
    dis[s] = 1;
    while(q.size()) {
         int u = q.front(); q.pop();
         for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == -1 && w[i]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
         }
    }
    return dis[t] != -1;
}

int dfs(int u, int f) {
    if(u == t || !f) {
        return f;
    }
    int use = 0;
    for(int &i = cur[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(w[i] && dis[v] == dis[u] + 1) {
            int a = dfs(v, min(f - use, w[i]));
            w[i] -= a, w[i ^ 1] += a, use += a;
            if(use == f) {
                break;
            }
        }
    }
    if(use == f) {
        dis[u] = -1;
    }
    return use;
}

int mxflow() {
    int res = 0;
    while(bfs()) {
        for(int i = 1 ; i <= cnt ; ++ i) {
            cur[i] = head[i];
        }
        res += dfs(s, inf);
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= m ; ++ j) {
            ids[i][j] = ++ cnt;
        }
    }
    s = ++ cnt, t = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) {
        int mx = -inf;
        for(int j = 1 ; j <= m ; ++ j) {
            scanf("%d", &X[i][j]);
            if(X[i][j] == -1) {
                X[i][j] = -inf;
            }
            mx = max(mx, X[i][j]);
        }
        add(s, ids[i][0], inf);
        for(int j = 1 ; j <= m ; ++ j) {
            add(ids[i][j - 1], ids[i][j], mx - X[i][j]);
        }
        add(ids[i][m], t, inf);

        ans += mx;
        assert(mx >= 0);
    }
    for(int i = 1, a, b ; i <= k ; ++ i) {
        scanf("%d%d", &a, &b);
        for(int j = 0 ; j < m ; ++ j) {
            add(ids[a][j], ids[b][j + 1], inf);
        }
    }
    ans -= mxflow();
    printf("%.2f\n", (double) ans / n);
}
