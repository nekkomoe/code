#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, k, cnt[26];
char s[N];
int main() {
	cin >> n >> k >> (s + 1);
	for(int i = 1 ; s[i] ; ++ i)
		cnt[s[i] - 'A'] ++;
	int mn = cnt[0];
	for(int i = 0 ; i < k ; ++ i) mn = min(mn, cnt[i]);
	cout << mn * k << endl;
}
