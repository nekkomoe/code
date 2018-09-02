#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int dis[N], mn[N][N], inq[N], a[N], n, m;
vector<pair<int, int> > g[N];
 
bool cmp(int a, int b) { return dis[a] < dis[b]; }
 
int main() {
    scanf("%d%d", &n, &m);
    memset(mn, 0x3f, sizeof mn);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        mn[u][v] = mn[v][u] = min(mn[u][v], w);
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
    queue<int> q;
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0, inq[1] = 1, q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for(int i = 0 ; i < g[u].size() ; ++ i) {
            int v = g[u][i].first, w = g[u][i].second;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if(!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) a[i] = i;
    sort(a + 1, a + 1 + n, cmp);
    long long ans = 1, prod, mod = (1ll << 31) - 1;
    for(int i = 2 ; i <= n ; ++ i) {
        prod = 0;
        for(int j = 1 ; j <= i - 1 ; ++ j) {
            int u = a[j], v = a[i];
            if(dis[u] + mn[u][v] == dis[v]) {
                ++ prod;
            }
        }
        (ans *= prod % mod) %= mod;
    }
    printf("%lld\n", ans);
}
