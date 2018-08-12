#include <bits/stdc++.h>
using namespace std;

const int N = 3010;
typedef long long ll;

int n, m;

ll ans = 1ll << 60;

vector<ll> pak[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y ; i <= n ; ++ i) {
		scanf("%d%d", &x, &y);
		pak[x].push_back(y);
	}
	for(int x = 1 ; x <= m ; ++ x) if(pak[x].size()) sort(pak[x].begin(), pak[x].end(), greater<ll>());
	for(int i = pak[1].size() ; i <= n ; ++ i) {
		priority_queue<ll, vector<ll>, greater<ll> > pq;
		ll sum = 0, cnt = i - pak[1].size();
		for(int j = 2 ; j <= m ; ++ j) {
			vector<ll> tmp = pak[j];
			while(tmp.size() && tmp.size() >= i) {
				-- cnt;
				sum += tmp.back();
				tmp.pop_back();
			}
			while(tmp.size()) {
				pq.push(tmp.back());
				tmp.pop_back();
			}
		}
		while(cnt > 0) -- cnt, sum += pq.top(), pq.pop();
		if(cnt <= 0) ans = min(ans, sum);
	}
	printf("%lld\n", ans);
}
