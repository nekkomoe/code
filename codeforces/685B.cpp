#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
vector<int> g[N];
int n, m, f[N], sz[N], mx[N], fa[N];
void dfs(int u) {
    sz[u] = 1;
    for(int v: g[u]) {
        dfs(v);
        sz[u] += sz[v];
        mx[u] = max(mx[u], sz[v]);
    }
    pair<int, int> idx = make_pair(mx[u], u);
    // printf("mx[%d] = %d\n", u, mx[u]);
    for(int v: g[u]) {
        int w = f[v];
        pair<int, int> cur = make_pair(max(mx[w], sz[u] - sz[w]), w);
        while(fa[w] != u) {
            w = fa[w];
            pair<int, int> upd = make_pair(max(mx[w], sz[u] - sz[w]), w);
            if(upd.first < cur.first) {
                cur = upd;
            } else {
                break;
            }
        }
        idx = min(idx, cur);
    }
    f[u] = idx.second;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 2, p ; i <= n ; ++ i) {
        scanf("%d", &p);
        fa[i] = p;
        g[p].push_back(i);
    }
    dfs(1);
    for(int i = 1, x ; i <= m ; ++ i) {
        scanf("%d", &x);
        printf("%d\n", f[x]);
    }
}
