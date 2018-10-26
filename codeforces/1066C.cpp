#include <bits/stdc++.h>
using namespace std; typedef long long ll; 

int main() {
	int q; scanf("%d", &q);
	int L = 0, R = 0, ini = 0;
	map<int, int> pos;
	for(int i = 1 ; i <= q ; ++ i) {
		char op[5]; int x; scanf("%s%d", op, &x);
		if(op[0] == 'L') {
			if(ini) -- L;
			ini = 1;
			pos[x] = L;
		} else if(op[0] == 'R') {
			if(ini) ++ R;
			ini = 1;
			pos[x] = R;
		} else {
			int ans = min(pos[x] - L, R - pos[x]);
			printf("%d\n", ans);
		}
//		if(op[0] != '?') printf("pos[%d] = %d\n", x, pos[x]);
	}
}
