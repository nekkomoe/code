#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;

struct Mat {
	ll a[30][30];
	ll* operator [] (int x) { return a[x]; }
	Mat() { memset(a, 0, sizeof a); }
} a;

Mat operator * (Mat a, Mat b) {
	Mat c;
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < n ; ++ j)
			for(int k = 0 ; k < n ; ++ k)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < n ; ++ j)
			scanf("%lld", &a[i][j]);
	Mat res;
	for(int i = 0 ; i < n ; ++ i) res[i][i] = 1;
	for(int i = 1 ; i <= k ; ++ i) res = res * a;
	printf("%lld\n", res[0][n - 1]);
}
