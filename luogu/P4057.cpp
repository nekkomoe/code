#include <bits/stdc++.h>
using namespace std;
// typedef __int128 ll;
typedef long long ll;

ll a, b, c;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	cin >> a >> b >> c;
	a = a / gcd(a, b) * b;
	a = a / gcd(a, c) * c;
	cout << a << endl;
}