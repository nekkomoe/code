#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 110;
int n; char s[N]; 
ll f[N][2], ans;

void sol() {
	for(int i = 0 ; i < n ; ++ i) {
		f[i + 1][0] = f[i + 1][1] = 0;
		
		if(s[i] == 'A') f[i + 1][0] = f[i][0] + f[i][1];
		else f[i + 1][0] = f[i][1];
		
		if(s[i + 1] == 'A') {
			if(s[i] == 'B')
				f[i + 1][1] = f[i][0];
		}
		else f[i + 1][1] = f[i][1];
	}
}

int main() {
	scanf("%s", s), n = strlen(s), s[n] = s[0];
	f[0][0] = 1, sol(), ans += f[n][0];
	f[0][0] = 0;
	f[0][1] = 1, sol(), ans += f[n][1];
	printf("%lld\n", ans);
}
