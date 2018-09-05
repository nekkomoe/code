#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 20;
ll n, dig[N], f[N][4][N];

int nxt(int st, int i) {
	if(st == 0) return i == 1;
	if(st == 1) return i == 3 ? 2 : i == 1;
	return st;
}

ll dfs(int pos, int st, int md, int bd) {
	if(pos == 0) {
		return st == 2 && md == 0;
	} else if(!bd && f[pos][st][md] != -1) {
		return f[pos][st][md];
	} else {
		int top = bd ? dig[pos] : 9;
		ll sum = 0;
		for(int i = 0 ; i <= top ; ++ i)
			sum += dfs(pos - 1, nxt(st, i), (md * 10 + i) % 13, bd && i == top);
		if(!bd) f[pos][st][md] = sum;
		return sum;
	}
}

void sol() {
	memset(f, -1, sizeof f);
	int pos = 0; while(n) dig[++ pos] = n % 10, n /= 10;
	cout << dfs(pos, 0, 0, 1) << endl;
} 

int main() {
	while(cin >> n) sol();
}
