#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	int n, m, ql, qr; cin >> n >> m >> ql >> qr, ++ ql;
	vector<int> a, b;
	for(int i = 1, x ; i <= n ; ++ i) cin >> x, a.push_back(x);
	for(int i = 1, x ; i <= m ; ++ i) cin >> x, b.push_back(x);
	sort(a.begin(), a.end()), sort(b.begin(), b.end());
	int l = a.back() + 1, r = *b.begin();
	
	bool flag = ql <= qr && l <= r && !(qr < l || r < ql);
	
	if(flag) puts("No War");
	else puts("War");
}
