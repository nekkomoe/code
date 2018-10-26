#include <bits/stdc++.h>
using namespace std; typedef long long ll;
int f[int(1e6) + 10]; const int inf = 1e9 + 10, N = 1e6 + 10;
struct T {
	int a, b, c, id;
} x[N], y[N];
bool operator < (T a, T b) { return a.a < b.a; }

int n, q, ans[N];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d%d%d", &x[i].c, &x[i].a, &x[i].b);
	scanf("%d", &q);
	for(int i = 1 ; i <= q ; ++ i) scanf("%d%d%d", &y[i].a, &y[i].b, &y[i].c), y[i].id = i;
	sort(x + 1, x + 1 + n), sort(y + 1, y + 1 + q);
	f[0] = inf;
	for(int i = 1, j = 1 ; i <= q ; ++ i) {
		while(j <= n && x[j].a <= y[i].a) {
			for(int k = 1e5 ; k >= x[j].c ; -- k) {
				f[k] = max(f[k], min(f[k - x[j].c], x[j].b));
			}
			++ j;
		}
		if(f[y[i].b] > y[i].a + y[i].c) ans[y[i].id] = 1;
	}
	for(int i = 1 ; i <= q ; ++ i) puts(ans[i] ? "TAK" : "NIE");
}
