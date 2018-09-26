#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
set<int> a[2][30];
char s[N], t[N];

int main() {
	cin >> s >> t;
	for(int i = 0 ; s[i] ; ++ i) a[0][s[i] - 'a'].insert(t[i] - 'a'),
		a[1][t[i] - 'a'].insert(s[i] - 'a');
	for(int i = 0 ; i < 26 ; ++ i)
		if(a[0][i].size() > 1 || a[1][i].size() > 1)
			return puts("No"), 0;
	puts("Yes"); 
}
