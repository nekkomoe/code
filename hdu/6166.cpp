#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m, k, s, t;
struct E { int v, w; };
vector<E> g[N];
const ll inf = 0x3f3f3f3f3f3f3f3fll;
ll dis[N]; int vis[N];

struct T { int u; ll w; };
bool operator < (T a, T b) { return a.w > b.w; }
void dij() {
    for(int i = 1 ; i <= n ; ++ i) dis[i] = inf, vis[i] = 0;
    priority_queue<T> pq;
    dis[s] = 0, pq.push((T) { s, 0 });
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(E e: g[u]) {
            int v = e.v, w = e.w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push((T) { v, dis[v] });
            }
        }
    }
}
int p[N];

void runprog() {
    scanf("%d%d", &n, &m);
    s = ++ n, t = ++ n;
    for(int i = 1 ; i <= n ; ++ i) {
        g[i].clear();
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((E) { v, w });
    }
    scanf("%d", &k);
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%d", &p[i]);
    }
    ll ans = inf;

    for(int r = 1 ; r <= 2 ; ++ r) {
        for(int T = 20 ; ~ T ; -- T) {
            g[s].clear(), g[t].clear();
            for(int _i = 1 ; _i <= k ; ++ _i) {
                int i = p[_i];
                if(g[i].size() && g[i].back().v == t) g[i].pop_back();
                if(_i & (1 << T)) {
                    g[s].push_back((E) { i, 0 });
                } else {
                    g[i].push_back((E) { t, 0 });
                }
            }
            dij();
            ans = min(ans, dis[t]);
        }
        reverse(p + 1, p + 1 + k);
    }
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    for(int i = 1 ; i <= t ; ++ i) {
        printf("Case #%d: ", i);
        runprog();
    }
}
