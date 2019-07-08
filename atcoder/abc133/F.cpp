#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
 
ll getinv(ll n) {
    return pw(n, mod - 2);
}
 
void upd(ll &a, ll b) {
    a = (a + b) % mod;
}
 
int n, q;
 
ll cnt[N]; // 记录每个颜色出现次数
ll sum[N]; // 记录每个颜色的边权和
ll S;
 
struct E {
    int v, c, w;
};
vector<E> g[N];
 
int fa[N][22], dep[N];
 
struct T {
    int ids;
    int x, y; // 把颜色x的长度都改成y
    int tag; // 对答案贡献 +-1
};
vector<T> nekko[N];
ll ans[N];
 
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i < n ; ++ i) {
        int u, v, c, w;
        scanf("%d%d%d%d", &u, &v, &c, &w);
        g[u].push_back((E) { v, c, w });
        g[v].push_back((E) { u, c, w });
    }
    if(1) {
        function<void(int, int)> dfs = [&] (int u, int fa) {
            dep[u] = dep[fa] + 1;
            :: fa[u][0] = fa;
            for(int i = 1 ; i <= 20 ; ++ i) {
                :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
            }
            for(auto e: g[u]) {
                int v = e.v;
                if(v != fa) {
                    dfs(v, u);
                }
            }
        };
        dfs(1, 0);
    }
 
    function<int(int, int)> getlca = [&] (int u, int v) {
        if(dep[u] < dep[v]) {
            swap(u, v);
        }
        for(int i = 20 ; ~ i ; -- i) {
            if(dep[fa[u][i]] >= dep[v]) {
                u = fa[u][i];
            }
        }
        if(u == v) {
            return u;
        }
        for(int i = 20 ; ~ i ; -- i) {
            if(fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    };
 
    for(int i = 1 ; i <= q ; ++ i) {
        int x, y, u, v;
        scanf("%d%d%d%d", &x, &y, &u, &v);
        int lca = getlca(u, v);
        nekko[u].push_back((T) { i, x, y, 1 });
        nekko[v].push_back((T) { i, x, y, 1 });
        nekko[lca].push_back((T) { i, x, y, -2 });
    }
    
    if(1) {
        function<void(int, int)> dfs = [&] (int u, int fa) {
            for(auto e: nekko[u]) {
                ll val = S - sum[e.x] + (ll) cnt[e.x] * e.y;
                ans[e.ids] += val * e.tag;
            }
            for(auto e: g[u]) {
                int v = e.v;
                if(v != fa) {
                    ++ cnt[e.c];
                    sum[e.c] += e.w;
                    S += e.w;
                    dfs(v, u);
                    -- cnt[e.c];
                    sum[e.c] -= e.w;
                    S -= e.w;
                }
            }
        };
        dfs(1, 0);
    }
 
    for(int i = 1 ; i <= q ; ++ i) {
        printf("%lld\n", ans[i]);
    }
}
