// 扩展欧几里德

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;

ll x, y, m, n, L, d, a, b, c;

void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if(!b) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b, d, y, x);
        y -= (a / b) * x;
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> x >> y >> m >> n >> L;
    a = ((n - m) % L + L) % L;
    b = L;
    c = ((x - y) % L + L ) % L;
    exgcd(a, b, d, x, y);
    if(c % d != 0) {
        puts("Impossible");
    } else {
        ll a1 = x * (c / d);
        ll a2 = abs(L / d);
        while(a1 < 0) {
            a1 += a2;
        }
        while(a1 >= a2) {
            a1 -= a2;
        }
        cout << a1 << endl;
    }
}
