#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int n, f[N];

void put(int x) {
	if(x) put(x / 10), putchar(x % 10 + '0');
}

int main() {
	int mx = 0, bt = 0;
	scanf("%d", &n);
	for(int i = 1, x ; i <= n ; ++ i) { scanf("%d", &x), ++ f[x]; mx = max(mx, x); }
	for(int t = mx ; t ; t >>= 1) ++ bt;
	for(int j = 0 ; j <= bt ; ++ j)
		for(int i = 1 ; i <= mx ; ++ i)
			if(i & (1 << j))
				f[i - (1 << j)] += f[i];
	for(int i = 0 ; i <= int(1e6) ; ++ i)
		if(f[i] == 0) puts("0");
		else put(f[i]), puts("");
}
