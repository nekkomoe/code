#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
vector<pair<int, int> > g[N];
int deg[N], vis[N], n, m, u[N], v[N], cnt[N];
queue<int> q;
int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1 ; i <= m ; ++ i) {
            scanf("%d%d", &u[i], &v[i]);
            ++ deg[u[i]], ++ deg[v[i]];
        }
        for(int i = 1 ; i <= m ; ++ i) {
            int x = u[i], y = v[i];
            if(deg[x] < deg[y]) swap(x, y);
            if(deg[x] == deg[y] && x > y) swap(x, y);
            g[x].push_back({ y, i });
        }
        for(int u = 1 ; u <= n ; ++ u) {
            for(auto v: g[u]) vis[v.first] = v.second;
            for(auto v: g[u])
                for(auto w: g[v.first])
                    if(vis[w.first])
                        ++ cnt[v.second], ++ cnt[w.second], ++ cnt[vis[w.first]];
            for(auto v: g[u]) vis[v.first] = 0;
        }
        long long ans = 0;
        for(int i = 1 ; i <= m ; ++ i) {
            ans += 1ll * cnt[i] * (cnt[i] - 1) / 2;
            cnt[i] = 0;
        }
        printf("%lld\n", ans);
        for(int i = 1 ; i <= n ; ++ i) g[i].clear(), deg[i] = 0;
    }
}
