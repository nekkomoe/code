#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n;

struct E {
    int v; ll w;
};
vector<E> g[N];

ll dfs(int u, int fa = 0) {
    ll res = 0;
    for(E e: g[u]) {
        int v = e.v;
        if(v != fa) {
            res = max(res, e.w + dfs(v, u));
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    ll ans = 0;
    for(int i = 1, u, v ; i < n ; ++ i) {
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        g[u].push_back((E) { v, w });
        g[v].push_back((E) { u, w });
        ans += w * 2;
    }
    printf("%lld\n", ans - dfs(1));
}
