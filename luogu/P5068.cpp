// luogu-judger-enable-o2
#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

const int N = 1010;

bitset<N> f[N][N], ans;
vector<int> g[N];

int dis[N][N], n, m, q;

void bfs(int s, int *dis) {
    queue<int> q; q.push(s);

    dis[s] = 0;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int v: g[u]) {
            if(dis[v] == 0x3f3f3f3f) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        if(dis[i] != 0x3f3f3f3f) {
            f[s][dis[i]].set(i);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        f[s][i] |= f[s][i - 1];
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dis, 0x3f, sizeof dis);
    for(int i = 1 ; i <= n ; ++ i) {
        bfs(i, dis[i]);
    }
    for(int i = 1 ; i <= q ; ++ i) {
        ans = 0;
        int k, st = 0; scanf("%d", &k);
        for(int j = 1, x, y ; j <= k ; ++ j) {
            scanf("%d%d", &x, &y);
            if(y <= n) {
                if(!st) {
                    st = 1;
                    ans = f[x][y];
                } else {
                    ans |= f[x][y];
                }
            }
        }
        printf("%d\n", int(ans.count()));
    }
}
