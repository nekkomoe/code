#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int head[N], rest[N], to[N], vis[N], n, m, tot;
ll w[N];
void add(int u, int v, ll c) {
    to[++ tot] = v, w[tot] = c, rest[tot] = head[u], head[u] = tot; 
}
ll a[65], dis[N];
void ins(ll x) {
    for(int i = 62 ; ~ i ; -- i) {
        if((x >> i) & 1) {
            if(!a[i]) {
                a[i] = x;
                break;
            }
            x ^= a[i];
        }
    }
}
void dfs(int u, int fa = 0) {
    vis[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i]; if(v == fa) continue;
        if(vis[v]) ins(dis[u] ^ dis[v] ^ w[i]);
        else dis[v] = dis[u] ^ w[i], dfs(v, u);
    }
}
int main() {
    scanf("%d%d", &n, &m);    
    for(int i = 1, u, v ; i <= m ; ++ i) {
        ll w;
        scanf("%d%d%lld", &u, &v, &w), add(u, v, w), add(v, u, w);
    }
    dfs(1);
    ll ans = dis[n];
    for(int i = 62 ; ~ i ; -- i)
        if((ans ^ a[i]) < ans)
            ans ^= a[i];
    printf("%lld\n", ans);
}


