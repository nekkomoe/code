#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

char s[N];

int n, nxt[N], f[N], bak[N];

int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	for(int i = 2, j = 0 ; i <= n ; ++ i) {
		while(j && s[i] != s[j + 1]) j = nxt[j];
		if(s[i] == s[j + 1]) ++ j;
		nxt[i] = j;
	}
	for(int i = 1 ; i <= n ; ++ i) {
		f[i] = i;
		if(bak[f[nxt[i]]] >= i - nxt[i]) f[i] = f[nxt[i]];
		bak[f[i]] = i;
	}
	printf("%d\n", f[n]);
}
