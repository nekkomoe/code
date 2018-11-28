#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 300000 + 10, neinf = 0xcfcfcfcf;

vector<int> g[N];
int n, m, from[N], to[N], cnt[N], deg[N], ans;

void poi(int *from, int *to) {
    for(int i = 1 ; i <= n ; ++ i) g[i].clear(), deg[i] = 0;
    queue<int> q;
    for(int i = 1 ; i <= m ; ++ i) {
        g[from[i]].push_back(to[i]);
        ++ deg[to[i]];
    }
    int tot = n;
    for(int i = 1 ; i <= n ; ++ i) {
        if(deg[i] == 0) {
            q.push(i);
            -- tot;
        }
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        if(q.empty()) {
            cnt[u] += tot;
        } else if(q.size() == 1) {
            int x = q.front(), flag = 1;
            for(int y: g[x]) {
                flag &= deg[y] > 1;
            }
            cnt[u] += flag * tot;
        } else {
            cnt[u] = neinf;
        }
        for(int v: g[u]) {
            if(! -- deg[v]) {
                q.push(v);
                -- tot;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &from[i], &to[i]);
    }
    poi(from, to), poi(to, from);
    for(int i = 1 ; i <= n ; ++ i)
        if(cnt[i] + 2 >= n)
            ++ ans;
    printf("%d\n", ans);
}

