#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
map<pair<int, int>, int> mp;
vector<int> pak[N];
int f[N], tot, n;
int main() {
	scanf("%d", &n);
	for(int i = 1, l, r ; i <= n ; ++ i) {
		scanf("%d%d", &l, &r);
		l ++, r = n - r;
		if(++ mp[make_pair(l, r)] == 1) pak[r].push_back(l);
	}
	for(int i = 1 ; i <= n ; ++ i) {
		f[i] = f[i - 1];
		for(int j = 0 ; j < pak[i].size() ; ++ j) {
			f[i] = max(f[i], f[pak[i][j] - 1] + min(mp[make_pair(pak[i][j], i)], i - pak[i][j] + 1));
		}
	}
	printf("%d\n", n - f[n]);
}
