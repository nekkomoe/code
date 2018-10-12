#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 1e3 + 10;

int n, a[N]; ll ans;

struct T {
	int l, r;
};
bool operator < (T a, T b) {
	return a.l < b.l;
}
vector<T> cnt[int(2 * 65536 + 10)];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d", &a[i]);
		a[i] ^= a[i - 1];
	}
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 0 ; j < i ; ++ j)
			cnt[a[i] ^ a[j]].push_back((T) { j + 1, i });
	for(int T = 0 ; T < int(2 * 65536 + 10) ; ++ T) {
        if(cnt[T].empty()) continue;
		cnt[T].push_back((:: T) { 0, 0 });
		sort(cnt[T].begin(), cnt[T].end());
		int sz = cnt[T].size() - 1;
		for(int i = 1 ; i <= sz ; ++ i) {
			int l = i + 1, r = sz, j = -1;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(cnt[T][mid].l > cnt[T][i].r) j = mid, r = mid - 1;
				else l = mid + 1;
			}
			if(~ j) ans += sz - j + 1;
		}
	}
	printf("%lld\n", ans);
}
