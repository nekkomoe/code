#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
int n, vis[N];
struct CIRCLE {
	double x, y, r, s;
} c[N];
bool operator < (CIRCLE a, CIRCLE b) {
	return a.r < b.r;
}

double pw(double a) { return a * a; }

double getdis(CIRCLE a, CIRCLE b) {
	return pw(a.x - b.x) + pw(a.y - b.y);
}

vector<int> g[N];

double ans;

double dfs(int u, int dep) {
	double res = 0; vis[u] = 1;
	for(int v: g[u])
		res += dfs(v, dep + 1);
	return dep == 0 ? res : res + ((dep & 1) ? 1 : -1) * c[u].s;
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].r),
		c[i].s = pw(c[i].r);
	sort(c + 1, c + 1 + n);
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = i + 1 ; j <= n ; ++ j) {
			if(getdis(c[i], c[j]) < pw(c[i].r + c[j].r)) {
				g[j].push_back(i);
				break;
			}
		}
	for(int i = n ; i ; -- i)
		if(!vis[i])
			ans += dfs(i, 0) + c[i].s;
	printf("%.9lf\n", acos(-1) * ans);
}