#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 500000 + 10;
int n, m, b[N]; ll a[N], ans;

template<typename T> inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

struct T { int nxt[N]; } t[2];

void sol(int bit) {
	int cnt = 0;
	for(int i = 1 ; i <= n ; ++ i) if(b[i] = ((a[i] >> bit) & 1)) ++ cnt;
	if(cnt & 1) { ans |= 1ll << bit; return ; }
	t[1] = t[0];
	for(int i = 1 ; i <= n ; ++ i) b[i] += b[i - 1];
	for(int i = 1 ; i <= n ; ) {
		int ql = i, qr = t[0].nxt[i];
		if((b[qr] - b[ql - 1]) & 1) {
			int j = qr + 1;
			while(j <= n) {
				int tl = j, tr = t[0].nxt[j];
				t[0].nxt[i] = t[0].nxt[j];
				if((b[tr] - b[tl - 1]) & 1) {
					break;
				}
				j = tr + 1;
			}
			i = j;
		} else {
			i = qr + 1;
		}
		
	}
	int tot = 0;
	for(int i = 1 ; i <= n ; i = t[0].nxt[i] + 1) {
		++ tot;
	}
	if(tot < m) {
		ans |= 1ll << bit;
		t[0] = t[1];
	}
}

int main() {
	read(n), read(m);
	for(int i = 1 ; i <= n ; ++ i) read(a[i]), t[0].nxt[i] = i;
	
	for(int bit = 60 ; ~ bit ; -- bit) {
		sol(bit);
	}
	printf("%lld\n", ans);
}
