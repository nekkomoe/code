#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int head[N], rest[N * 2], to[N * 2], w[N * 2];

void add(int u, int v, int w) {
    static int tot = 0;
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
} 

int _head[N], _rest[N * 2], _to[N * 2], _w[N * 2];
void _add(int u, int v, int w) {
    static int tot = 0;
    _to[++ tot] = v, _w[tot] = w, _rest[tot] =  _head[u], _head[u] = tot;
}

struct E {
    int u, v, w;
} e[N];

int n, m, ans[N], s, t;

ll dis[2][N], cnt[2][2][N];
const ll mod[2] = { (ll) (1e9 + 7), 998244853 };

int vis[N];
struct T {
    int u; ll w;
};
bool operator < (T a, T b) {
    return a.w > b.w;
}
const ll inf = 0x3f3f3f3f3f3f3f3fll;
void dij(ll *dis, ll cnt[2][N], int s, int t, int *head, int *rest, int *to, int *w) {
    for(int i = 1 ; i <= n ; ++ i) vis[i] = 0, dis[i] = inf;
    priority_queue<T> pq;
    pq.push((T) { s, dis[s] = 0 });
    cnt[0][s] = 1;
    cnt[1][s] = 1;
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue; vis[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], wi = w[i];
            if(dis[v] > dis[u] + wi) {
                dis[v] = dis[u] + wi;
                cnt[0][v] = cnt[0][u];
                cnt[1][v] = cnt[1][u];
                pq.push((T) { v, dis[v] });
            } else if(dis[v] == dis[u] + wi) {
                cnt[0][v] = (cnt[0][v] + cnt[0][u]) % mod[0];
                cnt[1][v] = (cnt[1][v] + cnt[1][u]) % mod[1];
            }
        }
    }
}

int main() {
//    freopen("data.in", "r", stdin);
    
    ios :: sync_with_stdio(0);
    cin >> n >> m >> s >> t;
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w);
        _add(v, u, w);
        e[i] = (E) { u, v, w };
    }
    dij(dis[0], cnt[0], s, t, head, rest, to, w);
    dij(dis[1], cnt[1], t, s, _head, _rest, _to, _w);
    
//    for(int i = 1 ; i <= n ; ++ i) cout << dis[0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << dis[1][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[0][0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[1][0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[0][1][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[1][1][i] << ' '; cout << endl;
    
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
//        cout << u << ' ' << v << ' ' << w << ' ' << (dis[0][u] + w + dis[1][v] == dis[0][t])
//        << ((cnt[0][0][u] * cnt[1][0][v]) % mod[0] == cnt[0][0][t])
//        << ((cnt[0][1][u] * cnt[1][1][v]) % mod[1] == cnt[0][1][t]) << endl; 
        if(dis[0][u] + w + dis[1][v] == dis[0][t]
        && (cnt[0][0][u] * cnt[1][0][v]) % mod[0] == cnt[0][0][t]
        && (cnt[0][1][u] * cnt[1][1][v]) % mod[1] == cnt[0][1][t]) {
           cout << "YES" << endl; 
        } else {
            ll del = dis[0][t] - dis[0][u] - dis[1][v];
            if(del <= 1) cout << "NO" << endl;
            else cout << "CAN " << w - del + 1 << endl; 
        }
    }
}
