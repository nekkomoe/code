#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
struct T {
	int a, id;
} t[N];
int mp[N];
void add(int x) {
	for( ; x <= n ; x += x & -x)
		++ mp[x]; 
}
int query(int x) {
	int r = 0;
	for( ; x ; x -= x & -x)
		r += mp[x];
	return r; 
}
bool cmp(T a, T b) { return a.a < b.a; }
int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &t[i].a), t[i].id = i;
	sort(t + 1, t + 1 + n, cmp);
	int ans = 1;
	for(int i = 1 ; i <= n ; ++ i)
		add(t[i].id),
		ans = max(ans, i - query(i));
	printf("%d\n", ans);
}
