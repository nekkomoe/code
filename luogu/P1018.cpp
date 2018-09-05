#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100;

struct Num {
	int a[N], len;
	Num() { len = 0, memset(a, 0, sizeof a); }
	void output() {
		for(int i = len - 1 ; ~ i ; -- i) printf("%d", a[i]);
		puts("");
	}
};

Num operator * (Num a, Num b) {
	Num c;
	int len = a.len + b.len;
	for(int i = 0 ; i < a.len ; ++ i)
		for(int j = 0 ; j < b.len ; ++ j)
			c.a[i + j] += a.a[i] * b.a[j];
	for(int i = 0 ; i < len ; ++ i)
		c.a[i + 1] += c.a[i] / 10, c.a[i] %= 10;
	while(c.a[len - 1] == 0 && len - 1 >= 1) -- len;
	c.len = len;
	return c;
}

Num f[60][10];

char s[60];

Num init(int n) {
	Num c;
	int len = n;
	for(int i = 1 ; i <= n ; ++ i) {
		c.a[n - i] = s[i] - '0';
	}
	while(c.a[len - 1] == 0 && len - 1 >= 1) -- len;
	c.len = len;
	return c;
}

Num get(int l, int r) {
	Num c;
	int len = r - l + 1;
	for(int i = l ; i <= r ; ++ i) {
		c.a[r - i] = s[i] - '0';
	}
	while(c.a[len - 1] == 0 && len - 1 >= 1) -- len;
	c.len = len;
	return c;
}

bool operator < (Num a, Num b) {
	if(a.len != b.len) return a.len < b.len;
	for(int i = a.len - 1 ; ~ i ; -- i)
		if(a.a[i] != b.a[i])
			return a.a[i] < b.a[i];
	return 0;
}

void read(Num &x) {
	memset(x.a, 0, sizeof x.a);
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(int i = 1 ; i <= n ; ++ i)
		x.a[n - i] = s[i] - '0';
	while(x.a[n - 1] == 0 && n - 1 >= 1) -- n;
	x.len = n;
}

int main() {
	
//	Num a, b;
//	read(a), read(b);
//	a.output(), b.output();
//	(a * b).output();
//	exit(0);
	
	int n, k;
	scanf("%d%d%s", &n, &k, s + 1);
	for(int i = 1 ; i <= n ; ++ i) {
		f[i][0] = init(i);
		for(int j = 1 ; j <= k ; ++ j) {
			for(int t = 1 ; t <= i - 1 ; ++ t) {
				f[i][j] = max(f[i][j], f[t][j - 1] * get(t + 1, i));
			}
		}
	}
	f[n][k].output();
}
