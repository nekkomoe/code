#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, x, y;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
	cin >> a >> b >> x >> y;
	ll d = gcd(x, y);
	x /= d, y /= d;
	cout << min(a / x, b / y);
}
