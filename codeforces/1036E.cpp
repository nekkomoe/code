#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
int cnt[N];

struct P {
	int x, y;
};
bool operator < (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y}; }
ll operator * (P a, P b) { return (ll) a.x * b.y - (ll) b.x * a.y; }

struct LINE {
	P a, b;
	ll d;
} ln[N];

ll ans;

set<P> s[N], glo;

ll x, y;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) {
		x = 1, y = 0;
	} else {
		exgcd(b, a % b, y, x);
		y -= x * (a / b);
	}
}

const P fl = (P) { (int) 1e7, (int) 1e7 };

bool in(ll x, ll l, ll r) {
	if(l > r) swap(l, r);
	return l <= x && x <= r;
}

P get(LINE a, LINE b) {
	ll x0 = a.a.x, y0 = a.a.y;
	ll u0 = (a.b.x - a.a.x) / a.d;
	ll v0 = (a.b.y - a.a.y) / a.d;
	
	ll x1 = b.a.x, y1 = b.a.y;
	ll u1 = (b.b.x - b.a.x) / b.d;
	ll v1 = (b.b.y - b.a.y) / b.d;
	
//	cout << "x0 = " << x0 << " y0 = " << y0 << endl;
//	cout << "u0 = " << u0 << " v0 = " << v0 << endl;
//	cout << "x1 = " << x1 << " y1 = " << y1 << endl;
//	cout << "u1 = " << u1 << " v1 = " << v1 << endl;
	
	ll up1 = (y1 - y0) * u0 - (x1 - x0) * v0;
	ll dw1 = u1 * v0 - v1 * u0;
	if(!dw1 || up1 % dw1) return fl;
	ll k1 = up1 / dw1;
	
	ll x = x1 + k1 * u1, y = y1 + k1 * v1;
	
//	cout << x << ' ' << y << endl;
	
	if(
	
	in(x, a.a.x, a.b.x) &&
	in(y, a.a.y, a.b.y) &&
	in(x, b.a.x, b.b.x) &&
	in(y, b.a.y, b.b.y)
	
	) {
		return (P) { x, y };
	} else {
		return fl;
	}
}

int main() {
//	freopen("data.in", "r", stdin);
	ios :: sync_with_stdio(0);
	int n; cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> ln[i].a.x >> ln[i].a.y >> ln[i].b.x >> ln[i].b.y;
		ln[i].d = gcd(abs(ln[i].a.x - ln[i].b.x), abs(ln[i].a.y - ln[i].b.y));
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			
//			if(i == 1 && j == 2)
			
			if(i != j) {
				P p = get(ln[i], ln[j]);
//				if(i == 1 && j == 2) {
//					cout << "( " << p.x << ", " << p.y << " )" << endl;
//				}
				if(p.x != 1e7) {
					s[i].insert(p);
					glo.insert(p);
				}
			}
		}
		ans += ln[i].d + 1 - s[i].size();
	}
	ans += glo.size();
//	cout << "glo.size() == " << glo.size() << endl;
//	for(auto v: glo) {
//		cout << "(" << v.x << ", " << v.y << ")" << endl;
//	}
	cout << ans << endl;
}
