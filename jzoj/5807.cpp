#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
int n, k, a[N];
ll s[N], ans, cnt[N];
void sol(int ql, int qr) {
	if(ql == qr) {
		return ;
	} else {
		int mid = (ql + qr) >> 1;
		sol(ql, mid), sol(mid + 1, qr);
		int l, r, mxl, mxr; ll sl, sr, sum;
		l = mid, r = mid + 1, mxl = a[l], mxr = a[r];
		sl = 0, sr = a[r] % k;
		++ cnt[sr];
		while(l >= ql) {
			mxl = max(mxl, a[l]);
			sl = (sl + a[l]) % k;
			while(r + 1 <= qr && mxl >= max(mxr, a[r + 1])) {
				++ r;
				mxr = max(mxr, a[r]);
				sr = (sr + a[r]) % k;
				++ cnt[sr];
			}
			if(mxl >= mxr) {
				ll qu = -sl + mxl;
				qu = (qu % k + k) % k;
				ans += cnt[qu];
			}
			-- l;
		}
		sum = 0; for(int i = mid + 1 ; i <= qr ; ++ i) cnt[sum = (sum + a[i]) % k] = 0;
		l = mid, r = mid + 1, mxl = a[l], mxr = a[r];
		sl = a[l] % k, sr = 0;
		++ cnt[sl];
		while(r <= qr) {
			mxr = max(mxr, a[r]);
			sr = (sr + a[r]) % k;
			while(l - 1 >= ql && mxr > max(mxl, a[l - 1])) {
				-- l;
				mxl = max(mxl, a[l]);
				sl = (sl + a[l]) % k;
				++ cnt[sl];
			}
			if(mxr > mxl) {
				ll qu = -sr + mxr;
				qu = (qu % k + k) % k;
				ans += cnt[qu];
			}
			++ r;
		}
		sum = 0; for(int i = mid ; i >= ql ; -- i) cnt[sum = (sum + a[i]) % k] = 0;
	}
}
int main() {
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &a[i]);
	sol(1, n);
	printf("%lld\n", ans);
}
