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
const int N = 6010;
const double inf = 1e60;
int n, m, k;
struct P { int x, y; } p[N];
int vis[N]; double dis[N];
double getdis(int i, int j) { return sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2)); }
int main() {
	freopen("starway.in", "r", stdin);
	freopen("starway.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1 ; i <= k ; ++ i) scanf("%d%d", &p[i].x, &p[i].y);
	for(int i = 1 ; i <= k ; ++ i) dis[i] = m - p[i].y;
	dis[k + 1] = m;
	dis[0] = inf;
	double ans = 0;
	while(1) {
		int id = 0;
		for(int i = 1 ; i <= k + 1 ; ++ i) if(!vis[i] && dis[i] < dis[id]) id = i;
		ans = max(ans, dis[id]);
		if(id == k + 1) break;
		for(int i = 1 ; i <= k ; ++ i) dis[i] = min(dis[i], getdis(i, id));
		dis[k + 1] = min(dis[k + 1], (double) p[id].y);
		vis[id] = 1;
	}
	printf("%.10lf\n", ans / 2);
}
