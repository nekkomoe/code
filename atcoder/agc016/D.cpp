#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e5 + 10;
int n, m, a[N], b[N], sa, sb, ans;

void WA() {
	puts("-1");
	exit(0);
}

bool check_unsolvable() {
	vector<int> x, y;
	x.push_back(sa), y.push_back(sb);
	for(int i = 1 ; i <= n ; ++ i) x.push_back(a[i]), y.push_back(b[i]);
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
//	for(int i = 0 ; i < x.size() ; ++ i)
//		cout << x[i] << ' ' << y[i] << endl;
	for(int i = 0 ; i < x.size() ; ++ i)
		if(x[i] != y[i])
			return 1;
	return 0;
}

int c[N], d[N]; 

map<int, int> tra;
int fa[N];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), sa ^= a[i];
	for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]), sb ^= b[i];
	if(check_unsolvable()) WA();
	
	int top = 0;
	for(int i = 1 ; i <= n ; ++ i)
		if(a[i] != b[i])
			c[++ top] = a[i],
			d[top] = b[i];
	c[++ top] = sa;
	d[top] = sb;
	n = top;
	int tot = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		a[i] = c[i];
		b[i] = d[i];
		if(!tra[a[i]]) tra[a[i]] = ++ tot;
	}
	ans = n - 1;
	
	if(!ans) return puts("0"), 0;
	
	for(int i = 1 ; i <= tot ; ++ i) fa[i] = i;
	for(int i = 1 ; i <= n ; ++ i) {
		if(a[i] != b[i]) {
			fa[get(tra[a[i]])] = get(tra[b[i]]);
		}
	}
	for(int i = 1 ; i <= tot ; ++ i)
		if(i == get(i))
			++ ans;
	printf("%d\n", ans - 1);
}
