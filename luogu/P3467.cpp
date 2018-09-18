#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
stack<int> s; int n, ans;
int main() {
	cin >> n;
	for(int i = 1, h ; i <= n ; ++ i) {
		scanf("%*d%d", &h);
		while(s.size() && h <= s.top())
			ans += s.top() == h,
			s.pop();
		s.push(h); 
	}
	cout << (n - ans) << endl;
}
