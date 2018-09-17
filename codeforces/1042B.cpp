#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
int n, ans[10];
int main() {
	cin >> n;
	memset(ans, 0x3f, sizeof ans);
	ans[0] = 0;
	for(int i = 1, c ; i <= n ; ++ i) {
		char s[5];
		cin >> c >> s;
		int b = 0; for(int j = 0 ; s[j] ; ++ j) b |= 1 << (s[j] - 'A'); 
		for(int s = 0 ; s < 8 ; ++ s) {
			for(int t = s ; ~ t ; t = (t - 1) & s) {
				if((b | t) == s)
					ans[s] = min(ans[s], ans[t] + c);
				if(!t) break;
			}
		}
	}
	cout << (ans[7] == 0x3f3f3f3f ? -1 : ans[7]) << endl;
}
