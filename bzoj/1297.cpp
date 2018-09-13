#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20, mod = 2009;

int n, tot, p[N][N];

struct Mat {
	ll a[100][100];
	Mat() {
		memset(a, 0, sizeof a);
	}
	ll* operator [] (int x) { return a[x]; }
	Mat operator * (Mat b) {
		Mat c;
		for(int i = 0 ; i < 100 ; ++ i)
			for(int k = 0 ; k < 100 ; ++ k)
				if(a[i][k])
					for(int j = 0 ; j < 100 ; ++ j)
						c[i][j] = (c[i][j] + a[i][k] * b[k][j] % mod) % mod;
		return c;
	}
} a;

Mat pw(Mat a, ll b) {
	Mat c;
	for(int i = 0 ; i < 100 ; ++ i) c[i][i] = 1;
	for( ; b ; b >>= 1, a = a * a)
		if(b & 1)
			c = c * a;
	return c;
}

char s[N];

int main() {
	ll T; scanf("%d%lld", &n, &T);
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j <= 9 ; ++ j)
			p[i][j] = tot ++;
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < 9 ; ++ j)
			a[p[i][j + 1]][p[i][j]] = 1;
	for(int i = 0 ; i < n ; ++ i) {
		scanf("%s", s);
		for(int j = 0 ; j < n ; ++ j) {
			int w = s[j] - '0';
			if(w) {
				a[p[i][0]][p[j][w - 1]] = 1;
			}
		}
	}
	Mat res = pw(a, T);
	printf("%lld\n", res[p[0][0]][p[n - 1][0]]);
}
