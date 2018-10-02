#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1500 + 10;
int n, q; char s[N];
int f[26][N];
int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> (s + 1) >> q;

	for(int c = 0 ; c < 26 ; ++ c)
		for(int i = 1 ; i <= n ; ++ i) {
			f[c][i] = i;
			if(s[i] == 'a' + c) f[c][0] = 1;
		}
	for(int c = 0 ; c < 26 ; ++ c) {
		for(int i = 1 ; i <= n ; ++ i) {
			for(int j = i, cnt = 0 ; j <= n ; ++ j) {
				cnt += 'a' + c != s[j];
				f[c][cnt] = max(f[c][cnt], j - i + 1);
			}
		}
	}

	for(int c = 0 ; c < 26 ; ++ c)
		for(int i = 1 ; i <= n ; ++ i)
			f[c][i] = max(f[c][i], f[c][i - 1]);

	for(int i = 1 ; i <= q ; ++ i) {
		int m; char op[10];
		cin >> m >> op;
		cout << f[op[0] - 'a'][m] << endl;
	}
}
