#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
char s[N];
int n;
int sa[N], h[N], zrk[N], x[N], y[N], a[N], b[N], tmp[N];
ll val[N], rk[N], cnt;
void getsa() {
	for(int i = 1 ; i <= n ; ++ i) x[s[i]] ++;
    for(int i = 0 ; i <= 256 ; ++ i) x[i] += x[i - 1];
    for(int i = n ; i >= 1 ; -- i) sa[x[s[i]] --] = i;
    for(int i = 0 ; i <= 256 ; ++ i) x[i] = 0;
    rk[sa[1]] = 1;
    for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for(int k = 1 ; rk[sa[n]] < n ; k <<= 1) {
        for(int i = 1 ; i <= n ; ++ i) x[i] = y[i] = 0;
        for(int i = 1 ; i <= n ; ++ i) x[a[i] = rk[i]] ++, y[b[i] = i + k > n ? 0 : rk[i + k]] ++;
        for(int i = 1 ; i <= n ; ++ i) x[i] += x[i - 1], y[i] += y[i - 1];
        for(int i = n ; i >= 1 ; -- i) tmp[y[b[i]] --] = i;
        for(int i = n ; i >= 1 ; -- i) sa[x[a[tmp[i]]] --] = tmp[i];
        rk[sa[1]] = 1;
        for(int i = 2 ; i <= n ; ++ i) rk[sa[i]] = rk[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]] || b[sa[i]] != b[sa[i - 1]]);
    }
	for(int i = 1 ; i <= n ; ++ i) zrk[sa[i]] = i, h[i] = 0;
	for(int i = 1, k = 0 ; i <= n ; ++ i) {
		if(k) -- k;
		for(int j = sa[zrk[i] - 1] ; s[i + k] == s[j + k] ; ++ k);
		h[zrk[i]] = k;
	}
}

vector<pair<int, int> > output;
int ans;

int H[N][21], lg[N];

void init() {
	for(int i = 1 ; i <= n ; ++ i)
		if((1 << lg[i - 1]) < i)
			lg[i] = lg[i - 1] + 1;
		else
			lg[i] = lg[i - 1];
	for(int i = 1 ; i <= n ; ++ i) H[i][0] = h[i];
	for(int j = 1 ; j <= 20 ; ++ j) {
		for(int i = 1 ; (i + (1 << j) - 1) <= n ; ++ i) {
			H[i][j] = min(H[i][j - 1], H[i + (1 << (j - 1))][j - 1]);
		}
	}
	rk[sa[1]] = n - sa[1] + 1;
	for(int i = 2 ; i <= n ; ++ i)
		rk[sa[i]] = rk[sa[i - 1]] - h[i] + n - sa[i] + 1;
	cnt = (ll) n * (n + 1) / 2;
	for(int i = 1 ; i <= n ; ++ i) cnt -= h[i];
}

int query(int l, int r) {
	if(l > r) swap(l, r);
	++ l;
	if(l == r) return H[l][0];
	else {
		int k = lg[r - l + 1] - 1;
		return min(H[l][k], H[r - (1 << k) + 1][k]);
	}
}

ll getrk(int l, int r) {
	int len = r - l + 1;
	if(len > h[zrk[l]]) return cnt - (rk[l] - (n - l + 1 - len)) + 1;
	else {
		int L = 1, R = zrk[l] - 1, t = 0;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(query(mid, zrk[l]) >= len) t = mid, R = mid - 1;
			else L = mid + 1;
		}
		return cnt - (rk[sa[t]] - (n - sa[t] + 1 - len)) + 1;
	}
}

void sol() {
	for(int i = 1 ; i <= n ; ++ i) {
		int l = i, r = n;
		while(l <= r) {
			int mid = (l + r) >> 1;
			ll rk = getrk(i, mid);
			ll sum = val[mid] - val[i - 1];
			if(sum > rk) r = mid - 1;
			else if(sum < rk) l = mid + 1;
			else {
				++ ans;
				output.push_back(make_pair(i, mid));
				break;
			}
		}
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1 ; i <= n ; ++ i) scanf("%lld", &val[i]), val[i] += val[i - 1];
	getsa();
	init();
	sol();
	printf("%d\n", ans);
	sort(output.begin(), output.end());
	for(int i = 0 ; i < output.size() ; ++ i) printf("%d %d\n", output[i].first, output[i].second);
}
