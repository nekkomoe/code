#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;

int n, a[N], q;
vector<pair<int, int> > g[N];
map<int, int> lst;

ll bit[N], ans[N], s[N];
void add(int x, ll y) {
    for( ; x <= n ; x += x & -x) {
        bit[x] ^= y;
    }
}

ll ask(int x) {
    ll res = 0;
    for( ; x ; x -= x & -x) {
        res ^= bit[x];
    }
    return res;
}

int main() {
#ifdef LOCAL_FILE
    freopen("data.in", "r", stdin);
#endif
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] ^ a[i];
    }
    scanf("%d", &q);
    for(int i = 1 ; i <= q ; ++ i) {
        int l, r; scanf("%d%d", &l, &r);
        g[r].push_back(make_pair(i, l));
        ans[i] = s[r] ^ s[l - 1];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int pos = lst[a[i]] + 1;
        add(pos, a[i]);
        add(i + 1, a[i]);
        lst[a[i]] = i;
        for(int j = 0 ; j < g[i].size() ; ++ j) {
            int id = g[i][j].first, l = g[i][j].second;
            ans[id] ^= ask(l);
        }
    }
    for(int i = 1 ; i <= q ; ++ i) {
        printf("%lld\n", ans[i]);
    }
}
