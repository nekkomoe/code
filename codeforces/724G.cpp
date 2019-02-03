#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;

int n, m, vis[N]; ll dis[N], a[65], ans; int cnt;
void ins(ll x) {
    for(int i = 60 ; ~ i ; -- i) {
        if(x & (1ll << i)) {
            if(!a[i]) {
                a[i] = x;
                ++ cnt;
                break;
            }
            x ^= a[i];
        }
    }
}
struct E { int v; ll w; };
vector<E> g[N];
int sta[N], top;
void dfs(int u, ll dep) {
    sta[++ top] = u;
    vis[u] = 1;
    dis[u] = dep;
    for(E e: g[u]) {
        int v = e.v; ll w = e.w;
        if(vis[v]) {
            ins(w ^ dep ^ dis[v]);
        } else {
            dfs(v, w ^ dep);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; ll w; scanf("%d%d%lld", &u, &v, &w);
        g[u].push_back((E) { v, w });
        g[v].push_back((E) { u, w });
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(!vis[i]) {
            memset(a, 0, sizeof a), top = cnt = 0;
            dfs(i, 0);
            for(int j = 60 ; ~ j ; -- j) {
                int flag = 0;
                for(int k = 60 ; ~ k ; -- k) {
                    if(a[k] & (1ll << j)) {
                        flag = 1;
                        break;
                    }
                }
                if(flag) {
                    ll tmp = ((1ll << (cnt - 1)) % mod)
                           * (((ll) top * (top - 1) / 2) % mod) % mod
                           * ((1ll << j) % mod) % mod;
                    ans = (ans + tmp ) % mod;
                } else {
                    ll x = 0;
                    for(int i = 1 ; i <= top ; ++ i) {
                        if(dis[sta[i]] & (1ll << j)) {
                            ++ x;
                        }
                    }
                    ll tmp = (x * (top - x) % mod)
                           * ((1ll << cnt) % mod) % mod
                           * ((1ll << j) % mod) % mod;
                    ans = (ans + tmp) % mod;
                }
            }
        }
    }
    printf("%lld\n", ans);
}
