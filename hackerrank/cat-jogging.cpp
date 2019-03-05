#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int rk[N], id[N], deg[N], n, m, cnt[N];
vector<int> g[N], gtr[N];
bool cmp(int a, int b) { return deg[a] < deg[b]; }

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v), g[v].push_back(u);
        ++ deg[u], ++ deg[v];
    }
    for(int i = 1 ; i <= n ; ++ i) id[i] = i;
    sort(id + 1, id + 1 + n, cmp);
    for(int i = 1 ; i <= n ; ++ i) rk[id[i]] = i;
    for(int u = 1 ; u <= n ; ++ u)
        for(int v: g[u])
            if(rk[v] > rk[u])
                gtr[u].push_back(v);
    ll ans = 0;
    for(int u = 1 ; u <= n ; ++ u) {
        for(int v: g[u])
            for(int z: gtr[v])
                if(rk[z] > rk[u])
                    ans += cnt[z] ++;
        for(int v: g[u])
            for(int z: gtr[v])
                if(rk[z] > rk[u])
                    cnt[z] = 0;
    }
    printf("%lld\n", ans);
}

