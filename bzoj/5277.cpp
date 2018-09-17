#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N];
struct T { int a, id; } t[N];
bool cmp(T a, T b) { return a.a == b.a ? a.id < b.id : a.a < b.a; }
int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &t[i].a), t[i].id = i;
	sort(t + 1, t + 1 + n, cmp);
	if(n == 1) return puts("0"), 0; 
	long long ans = 0;
	for(int i = 1, mx = 0 ; i < n ; ++ i) a[i] = (mx = max(mx, t[i].id)) - i;
	for(int i = 1 ; i <= n ; ++ i) ans += max(max(a[i - 1], a[i]), 1);
	printf("%lld\n", ans);
}
