#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10, mod = 998244353;

int n, m;
int id[N];
set<int> st[N];
void merge(int &x, int y) {
    if(st[x].size() < st[y].size()) swap(x, y);
    for(int z: st[y]) st[x].insert(z);
}

int main() {
    // freopen("graph.in", "r", stdin);
    // freopen("graph.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        st[u].insert(v);
    }
    ll ans = 1;
    for(int i = 1 ; i <= n ; ++ i) id[i] = i;
    for(int i = 1 ; i <= n ; ++ i) {
        while(st[id[i]].size() && *st[id[i]].begin() == i) st[id[i]].erase(st[id[i]].begin());
        ans = ans * (n - st[id[i]].size()) % mod;
        if(st[id[i]].size()) merge(id[*st[id[i]].begin()], id[i]);
    }
    printf("%lld\n", ans);
}
