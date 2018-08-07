#include <bits/stdc++.h>
using namespace std;
const int p = 1e9 + 7, N = 20;
typedef long long ll;
int pw(int a, int b) {
	int r = 1;
	for( ; b ; b >>= 1, a = 1ll * a * a % p) if(b & 1) r = 1ll * r * a % p;
	return r;
}
int calc(int n, ll b) {
	if(b < 0) return 0;
	int r = 1;
	for(int i = 1 ; i < n ; ++ i) r = 1ll * r * pw(i, p - 2) % p;
	for(int i = 1 ; i < n ; ++ i) r = 1ll * r * (b + i) % p;
	return r;
}
int cnt[1 << 20], total, k1, k2, L1[N], R1[N], L2[N], R2[N];
int getans(int ty) {
	ll b = -1;
	if(ty == 1) {
		for(int i = 1 ; i <= k1 ; ++ i) b += R1[i];
		for(int i = 1 ; i <= k2 ; ++ i) b += -L2[i];
	} else {
		for(int i = 1 ; i <= k2 ; ++ i) b += R2[i];
		for(int i = 1 ; i <= k1 ; ++ i) b += -L1[i];
	}
	int ans = 0;
	for(int s = 0 ; s < 1 << (k1 + k2) ; ++ s) {
		int sig = (cnt[s] & 1) ? -1 : 1;
		ll B = b;
		for(int i = 1 ; i <= k1 ; ++ i) {
			if((s >> (i - 1)) & 1) {
				B -= R1[i] - L1[i] + 1;
			}
		}
		for(int i = 1 ; i <= k2 ; ++ i) {
			if((s >> (k1 + i - 1)) & 1) {
				B -= R2[i] - L2[i] + 1;
			}
		}
		ans = (ans + 1ll * sig * calc(k1 + k2 + 1, B)) % p;
	}
	return (1ll * ans % p + p) % p * total % p;
}
void sol() {
	total = 1;
	scanf("%d", &k1);
	for(int i = 1 ; i <= k1 ; ++ i) {
		scanf("%d%d", &L1[i], &R1[i]);
		total = (1ll * total * pw(R1[i] - L1[i] + 1, p - 2)) % p;
	}
	scanf("%d", &k2);
	for(int i = 1 ; i <= k2 ; ++ i) {
		scanf("%d%d", &L2[i], &R2[i]);
		total = (1ll * total * pw(R2[i] - L2[i] + 1, p - 2)) % p;
	}
	int ans1 = getans(1), ans3 = getans(3), ans2 = ((1 - ans1 - ans3) % p + p) % p;
	printf("%d %d %d\n", ans1, ans2, ans3);
}
int main() {
	for(int i = 1 ; i < (1 << 20) ; ++ i) cnt[i] = cnt[i >> 1] + (i & 1);
	int T; scanf("%d", &T);
	while(T --) sol();
}
