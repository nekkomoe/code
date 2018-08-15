%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
struct TT { int to; ll w; };
bool operator < (TT a, TT b) { return a.w > b.w; }
vector<TT> g[N];
struct E { int u, v, t, c; } e[N];
bool operator < (E a, E b) { return a.t < b.t; }
int S, T;
ll dis[N];
int vis[N], n, m;
int fa[N];
ll dij() {
	priority_queue<TT> pq;
	for(int i = 1 ; i <= n ; ++ i) dis[i] = 1ll << 60, vis[i] = 0;
	pq.push((TT) { S, dis[S] = 0 });
	while(pq.size()) {
		int u = pq.top().to; pq.pop();
		if(vis[u]) continue; vis[u] = 1;
		for(auto e: g[u])
			if(dis[e.to] > dis[u] + e.w)
				pq.push((TT) { e.to, dis[e.to] = dis[u] + e.w });
	}
	return dis[T];
}
int get(int x) { return fa[x] == x ? fa[x] : fa[x] = get(fa[x]); }
int main() {
	freopen("running.in", "r", stdin);
	freopen("running.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1 ; i <= m ; ++ i) scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].t, &e[i].c);
	scanf("%d%d", &S, &T);
	sort(e + 1, e + 1 + m);
	iota(fa + 1, fa + 1 + n, 1);
	for(int i = 1 ; i <= m ; ++ i) {
		int u = e[i].u, v = e[i].v, t = e[i].t, c = e[i].c;
		fa[get(u)] = get(v);
		g[u].push_back((TT) { v, 1ll * t * c });
		g[v].push_back((TT) { u, 1ll * t * c });
		if(get(S) == get(T) && (i == m || t != e[i + 1].t)) {
			printf("%d %lld\n", t, dij());
			break;
		}
	}
}
