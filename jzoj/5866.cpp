#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
struct P {
	int op, x, y;
} t[N * 2];
bool cmp(P a, P b) {
	if(a.x != b.x) return a.x > b.x;
	else if(a.op != b.op) return a.op > b.op;
	else return a.y < b.y;
}
bool operator < (P a, P b) {
	return a.y < b.y;
}
multiset<P> s;

int main() {
	freopen("guide.in", "r", stdin);
	freopen("guide.out", "w", stdout);
	scanf("%*d%d", &n);
	for(int i = 1 ; i <= n ; ++ i) t[i].op = 1, scanf("%d%d", &t[i].x, &t[i].y);
	for(int i = n + 1 ; i <= 2 * n ; ++ i) t[i].op = 2, scanf("%d%d", &t[i].x, &t[i].y);
	sort(t + 1, t + 1 + 2 * n, cmp);
	int ans = 0;
	for(int i = 1 ; i <= 2 * n ; ++ i) {
		if(t[i].op == 2) {
			s.insert(t[i]);
		} else {
			auto x = s.lower_bound(t[i]);
			if(x != s.end()) {
				s.erase(x);
				++ ans;
			}
		}
	}
	printf("%d\n", ans);
}
