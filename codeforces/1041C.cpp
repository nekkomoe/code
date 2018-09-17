#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m, d;
struct T { int a, id; } t[N]; 
bool operator < (T a, T b) { return a.a < b.a; }
int ans[N];
deque<pair<int, int> > q;
int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> m >> d;
	for(int i = 1 ; i <= n ; ++ i) cin >> t[i].a, t[i].id = i;
	sort(t + 1, t + 1 + n);
	int day = 0;
	for(int i = 1, j = 2 ; i <= n ; ++ i) {
		if(j <= i) j = i + 1; 
		if(!ans[t[i].id]) ans[t[i].id] = ++ day;
		while(t[j].a - t[i].a - 1 < d && j + 1 <= n) ++ j;
		while(ans[t[j].id] && j + 1 <= n) ++ j;
		if(t[j].a - t[i].a - 1 >= d && !ans[t[j].id]) ans[t[j].id] = ans[t[i].id];
	} 
	cout << day << endl;
	for(int i = 1 ; i <= n ; ++ i) cout << ans[i] << ' ';
}
