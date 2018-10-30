#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 610;
int V, e, n, m;
struct E { int v, w; }; vector<E> G[N];

int a[N], lk[210][N];
int mindis[N][N];

int vis[N], mat[N], T;

int dfs(int u) {
//	printf("u = %d\n", u);
	for(int v = 1 ; v <= V ; ++ v) {
		if(lk[u][v] && vis[v] != T) {
			vis[v] = T;
			if(!mat[v] || dfs(mat[v])) {
				mat[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int getmx() {
	int res = 0; for(int i = 1 ; i <= V ; ++ i) mat[i] = 0;
	for(int i = 1 ; i <= n ; ++ i) {
        ++ T;
        if(dfs(i)) {
            ++ res;
        }
    }
    return res;
}

bool check(int mid) {
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= V ; ++ j)
			lk[i][j] = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		int u = a[i];
		for(int v = 1 ; v <= V ; ++ v) {
			if(mindis[u][v] <= mid) {
				lk[i][v] = 1;
			}
		}
	}
	return getmx() >= m;
}

int main() {
	scanf("%d%d%d%d", &V, &e, &n, &m);
	memset(mindis, 0x3f, sizeof mindis);
	for(int i = 1 ; i <= V ; ++ i) mindis[i][i] = 0;
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
	for(int i = 1, u, v, w ; i <= e ; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back((E) { v, w });
		G[v].push_back((E) { u, w });
		mindis[u][v] = mindis[v][u] = min(mindis[u][v], w);
	}
	for(int k = 1 ; k <= V ; ++ k)
		for(int i = 1 ; i <= V ; ++ i)
			for(int j = 1 ; j <= V ; ++ j)
				mindis[i][j] = min(mindis[i][j], mindis[i][k] + mindis[k][j]);
	int l = 0, r = 1731311, ans = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
}
