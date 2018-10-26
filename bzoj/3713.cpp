#include <bits/stdc++.h>
using namespace std; typedef long long ll;

ll f[110];

void sol() {
	ll n; scanf("%lld", &n);
	for(int i = 0 ; i <= 45 ; ++ i)
		for(int j = i ; j <= 45 ; ++ j)
			if(f[i] * f[j] == n)
				return puts("TAK"), void();
	puts("NIE");
}

int main() {
	f[0] = 0, f[1] = 1;
	for(int i = 2 ; i <= 45 ; ++ i) f[i] = f[i - 1] + f[i - 2];
	int t; scanf("%d", &t);
	while(t --) sol();
}
