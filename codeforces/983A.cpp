#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, p, q, b;

template<typename T> inline void read(T &x) {
	char c = x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

void sol() {
	read(p), read(q), read(b);
	q /= __gcd(p, q);
	while(1) {
		b = __gcd(b, q);
		if(b == 1 && q == 1) return puts("Finite"), void();
		else if(b == 1) return puts("Infinite"), void();
		while(!(q % b)) q /= b;
	}
}

int main() {
	read(n);
	while(n --) sol(); 
}
