#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
 
using namespace std;
const int N = 71000;
typedef long long ll;
typedef pair<ll, int> pr;
 
int n, m, head[N], rest[N], to[N], vis[N], c[N], tot;
ll len[N], f[N], g[N];
priority_queue<pr> q;
vector<int> p[N];
 
int main() {
    memset(f, 0x3f, sizeof f), memset(g, 0x3f, sizeof g);
    scanf("%d%d", &n, &m);
    for(int i = 1, u ; i <= m ; ++ i) {
        ++ tot;
        scanf("%d%d%lld", &u, &to[tot], &len[tot]);
        rest[tot] = head[u];
        head[u] = tot;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &c[i]);
        for(int j = 1, x ; j <= c[i] ; ++ j) scanf("%d", &x), p[x].push_back(i);
        if(!c[i]) g[i] = 0;
    }
    f[1] = 0;
    q.push(pr(0, 1));
    while(q.size()) {
        ll dis = -q.top().first;
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(f[v] > dis + len[i]) {
                f[v] = dis + len[i];
                if(!c[v]) q.push(pr(-max(f[v], g[v]), v));
            }
        }
        for(int j = 0 ; j < p[u].size() ; ++ j) {
            int v = p[u][j];
            if(!-- c[v]) g[v] = dis, q.push(pr(-max(f[v], g[v]), v));
        }
    }
    printf("%lld\n", max(f[n], g[n]));
}
