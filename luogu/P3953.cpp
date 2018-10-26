#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
int dis_n[N], n, m, k, p;
int head[N], rest[N * 2], to[N * 2], w[N * 2], tot, vis[N];
void add(int u, int v, int w) { to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot; }

struct T { int u, dis; };
bool operator < (T a, T b) { return a.dis > b.dis; }

void dij(int s, int *dis) {
    for(int i = 1 ; i <= n ; ++ i) vis[i] = 0, dis[i] = 1e9 + 10;
    priority_queue<T> pq;
    pq.push((T) { s, 0 }), dis[s] = 0;
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue; vis[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + w[i]) {
                dis[v] = dis[u] + w[i];
                pq.push((T) { v, dis[v] });
            }
        }
    }
}

struct E { int u, v, w; }; vector<E> e;
int ins[N][55]; ll f[N][55]; int vvv[N][55];
ll dfs(int u, int k) {
	if(ins[u][k]) return -1;
//	if(f[u][k]) return f[u][k];
	if(vvv[u][k]) return f[u][k];
	vvv[u][k] = 1;
	ll res = u == n;
	
	ins[u][k] = 1;
	
	for(int i = head[u] ; i ; i = rest[i]) {
		int v = to[i];
		ll dis = dis_n[v] - dis_n[u] + w[i];
		if(dis <= k) {
			ll t = dfs(v, k - dis);
			if(t == -1) return ins[u][k] = 0, f[u][k] = -1;
			res = (res + t) % p;
		}
	}
	
	ins[u][k] = 0;
	return f[u][k] = res;
}

void sol() {
    scanf("%d%d%d%d", &n, &m, &k, &p);
    memset(head, 0, sizeof head), tot = 0;
    e.clear();
    for(int i = 1, u, v, w ; i <= m ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
		add(v, u, w);
		e.push_back((E) { u, v, w });
    }
    dij(n, dis_n);
    memset(head, 0, sizeof head), tot = 0;
    for(E e: :: e) add(e.u, e.v, e.w);
    
//    memset(f, 0, sizeof f);
    memset(vvv, 0, sizeof vvv);
    
    printf("%lld\n", dfs(1, k));
}

int main() {
//	freopen("data.in", "r", stdin);
    int T; scanf("%d", &T);
    while(T --) sol();
}
