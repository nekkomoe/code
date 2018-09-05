#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1010;
struct Man { int a, b; } man[N];
bool operator < (Man a, Man b) { return a.a * a.b < b.a * b.b; }
int n, a, b;

struct Num {
	int a[5000], n;
	void init() { n = 0, memset(a, 0, sizeof a); }
	Num() { init(); }
	void output() {
		for(int i = n - 1 ; ~ i ; -- i) {
			printf("%d", a[i]);
		}
		puts("");
	}
};

Num operator * (Num a, Num b) {
	Num c;
	int n = a.n + b.n;
	for(int i = 0 ; i < a.n ; ++ i)
		for(int j = 0 ; j < b.n ; ++ j)
			c.a[i + j] += a.a[i] * b.a[j];
	for(int i = 0 ; i < n ; ++ i)
		c.a[i + 1] += c.a[i] / 10, c.a[i] %= 10;
	while(n > 1 && c.a[n - 1] == 0) -- n;
	c.n = n;
	return c;
}

Num operator - (Num a, Num b) {
	Num c;
	int n = a.n + b.n;
	for(int i = 0 ; i < n ; ++ i) c.a[i] = a.a[i] - b.a[i];
	for(int i = 0 ; i < n ; ++ i) {
		while(c.a[i] < 0) {
			-- c.a[i + 1];
			c.a[i] += 10;
		}
	}
	while(n > 1 && c.a[n - 1] == 0) -- n;
	c.n = n;
	return c;
}

Num operator / (Num a, int x) {
//	cout << endl;
//	cout << "/" << endl;
//	a.output();
//	cout << x << endl;
//	cout << endl;
	
	Num b;
	int n = 0, flag = 0, tot = 0;
	for(int i = a.n - 1 ; ~ i ; -- i) {
		tot = tot * 10 + a.a[i];
		if(tot / x) {
			flag = 1;
			b.a[n ++] = tot / x;
		} else if(flag) {
			b.a[n ++] = 0;
		}
		tot %= x;
	}
//	cout << "n = " << n << endl;
	if(n == 0) n = 1;
	else reverse(b.a, b.a + n);
	b.n = n;
	return b;
}

Num to(int x) {
	Num a;
	int n = 0;
	while(x) a.a[n ++] = x % 10, x /= 10;
	if(n == 0) n = 1;
	a.n = n;
	return a;
}

bool operator < (Num a, Num b) {
	if(a.n != b.n) return a.n < b.n;
	for(int i = a.n - 1 ; ~ i ; -- i)
		if(a.a[i] != b.a[i])
			return a.a[i] < b.a[i];
	return 0;
}

int main() {
	scanf("%d", &n);
	scanf("%d%d", &a, &b);
	for(int i = 1 ; i <= n ; ++ i) {
		scanf("%d%d", &man[i].a, &man[i].b);
	}
	sort(man + 1, man + 1 + n);
	
	Num pro = to(a), ans;
	for(int i = 1 ; i <= n ; ++ i) {
		Num x = pro / man[i].b;
		ans = max(ans, x);
		pro = pro * to(man[i].a);
	}
	ans.output();
}
