#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct T { int a, id; } t[N];
bool cmp(T a, T b) {
	return a.a < b.a;
}
int n, tot;
void tmp() {
	-- tot;
	if(!tot) exit(0);
}
int main() {
	ios :: sync_with_stdio(0);
	cin >> n, tot = n;
	int cnt0 = 0, cntlt0 = 0, cntgt0 = 0;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> t[i].a, t[i].id = i;
		if(t[i].a == 0) ++ cnt0;
		else if(t[i].a < 0) ++ cntlt0;
		else ++ cntgt0;
	}
	sort(t + 1, t + 1 + n, cmp);
	for(int i = 1 ; i <= n ; ++ i) {
		if(t[i].a == 0) {
			for(int j = i + 1 ; j <= n ; ++ j) {
				if(t[j].a == 0) {
					tmp();
					printf("1 %d %d\n", t[j].id, t[i].id);
					t[j].a = 1e9 + 10;
				} else break;
			}
			break;
		}
	}
	sort(t + 1, t + 1 + n, cmp);
	while(n >= 1 && t[n].a == 1e9 + 10) -- n;
	if(n) {
		if(cnt0) {
			if(cntlt0 & 1) {
				for(int i = 1 ; i <= n ; ++ i) {
					if(t[i].a == 0) {
						if(i - 1 >= 1) {
							tmp();
							printf("1 %d %d\n", t[i - 1].id, t[i].id);
							t[i - 1].a = 1e9 + 10;
						}
						tmp();
						printf("2 %d\n", t[i].id);
						t[i].a = 1e9 + 10;
						break;
					}
				}
			} else {
				for(int i = 1 ; i <= n ; ++ i) {
					if(t[i].a == 0) {
						tmp();
						printf("2 %d\n", t[i].id);
						t[i].a = 1e9 + 10; 
						break;
					}
				}
			}
		} else {
			if(cntlt0 & 1) {
				for(int i = n ; i ; -- i) {
					if(t[i].a < 0) {
						tmp();
						printf("2 %d\n", t[i].id);
						t[i].a = 1e9 + 10;
						break;
					}
				}
			}
		}
		sort(t + 1, t + 1 + n, cmp);
		while(n >= 1 && t[n].a == 1e9 + 10) -- n;
		for(int i = 1 ; i < n ; ++ i) {
			int x = t[i + 1].id;
			tmp(); 
			printf("1 %d %d\n", t[i].id, x);
		}
	}
}
