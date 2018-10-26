#include <bits/stdc++.h>
using namespace std; typedef long long ll;
int d, s;

struct T {
	int d, s;
	string str;
};

queue<T> q; bool vis[5010][5010];

int main() {
	scanf("%d%d", &d, &s);
	q.push((T) { 0, 0, "" });
	vis[0][0] = 1;
	while(q.size()) {
		T u = q.front(); q.pop();
		if(u.d == 0 && u.s == s) return puts(u.str.c_str()), 0;
		for(int i = 0 ; i <= 9 ; ++ i) {
			int d = (u.d * 10 + i) % :: d;
			int s = u.s + i;
			if(s <= :: s && !vis[d][s]) {
				vis[d][s] = 1;
				q.push((T) { d, s, u.str + char(i + '0') });
			}
		}
	}
	puts("-1");
}
