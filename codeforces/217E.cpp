#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
crope c; const int N = 5010;
int n, k, l[N], r[N], len[N]; char s[int(3e6) + 10];

int main() {
	ios :: sync_with_stdio(0);
	cin >> s >> k >> n;
	for(int i = 1 ; i <= n ; ++ i) cin >> l[i] >> r[i], len[i] = r[i] - l[i] + 1;
	for(int i = n ; i ; -- i)
		if(r[i] < k)
			len[i] = min(len[i], k - r[i]),
			k -= len[i];
		else len[i] = 0;
	s[k] = 0, c.insert(0, s);
	for(int i = 1 ; i <= n ; ++ i)
		if(len[i]) {
			string s;
			for(int j = l[i] ; j < r[i] && s.length() < len[i] ; j += 2)
				s += c[j];
			for(int j = l[i] - 1 ; j < r[i] && s.length() < len[i] ; j += 2)
				s += c[j];
			c.insert(r[i], s.c_str());
		}
	cout << c << endl;
}
