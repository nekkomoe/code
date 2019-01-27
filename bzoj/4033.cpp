#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int N = 4100;
 
typedef long long ll;
 
int n, k, head[N], rest[N], to[N], tot;
 
ll len[N];
 
void add(int u, int v, ll w) {
    to[++ tot] = v, len[tot] = w, rest[tot] = head[u], head[u] = tot;
}
 
int sz[N];
 
ll f[2100][2100], dist[N];
 
void dfs(int u, int fa) {
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    f[u][0] = f[u][1] = 0;
    if(sz[u] == 1) return;
    ll sum = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        for(int j = sum ; j >= 0 ; -- j) {
            for(int x = min(k, sz[v]) ; x >= 0 ; -- x) {
                if(f[v][x] >= 0 && x + j <= k) {
                    f[u][x + j] = max(f[u][x + j], f[v][x] + f[u][j] + len[i] * ((ll) x * (k - x) + ((ll) sz[v] - x) * (n - k - sz[v] + x)));
                }
            }
        }
        sum = min((ll) k, sum + sz[v]);
    }
}
 
int main() {
    memset(f, -1, sizeof f);
    scanf("%d%d", &n, &k);
    for(int i = 1, u, v, w ; i < n ; ++ i) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
    dfs(1, 0);
    printf("%lld\n", f[1][k]);
}
