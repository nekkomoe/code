#pragma GCC optimize(2)
#pragma GCC optimize(3)
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 5010;
int n;
vector<int> g[N];
int cnt[N], tmp[N]; ll ans, tot;
ll sum[N];

ll calc(ll n) { return n * (n - 1) / 2; }

void dfs(int u, int fa, int dep) {
    ans += cnt[dep];
    ++ cnt[dep];
    ++ tmp[dep];
    tot += calc(cnt[dep] - tmp[dep]) - sum[dep];
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v != fa)
            dfs(v, u, dep + 1);
	}
}

void put(int u, int fa, int dep) {
    if(tmp[dep]) {
        sum[dep] += calc(tmp[dep]);
        tmp[dep] = 0;
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v != fa)
            put(v, u, dep + 1);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int u = 1 ; u <= n ; ++ u) {
        memset(cnt, 0, sizeof cnt);
        memset(sum, 0, sizeof sum);
        for(int i = 0 ; i < g[u].size() ; ++ i) {
        	int v = g[u][i];
            dfs(v, u, 1);
            put(v, u, 1);
        }
    }
    printf("%lld\n", tot);
}
