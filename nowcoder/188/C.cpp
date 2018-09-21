#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 50000 + 10;
 
struct E { int v, w; };
 
vector<E> g[N];
 
ll dfs(int u, int fa) {
    ll res = 0;
    for(E e: g[u]) {
        int v = e.v;
        if(v != fa) {
            res = max(res, dfs(v, u) + e.w);
        }
    }
    return res;
}
 
int main() { int n, m;
    scanf("%d%d", &n, &m);
    ll sum = 0;
    for(int i = 1, u, v, w ; i < n ; ++ i) scanf("%d%d%d", &u, &v, &w), g[u].push_back((E) { v, w }), g[v].push_back((E) { u, w }), sum += 1ll * w + w;
    printf("%lld\n", sum - dfs(m, 0));
}
