#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 1e5 + 10;
 
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
 
ll getinv(ll n) {
    return pw(n, mod - 2);
}
 
int main() {
    ll w, h, x, y;
    cin >> w >> h >> x >> y;
    int flag = 0;
    if(x * 2 == w && y * 2 == h) {
        flag = 1;
    }
    cout << fixed << setprecision(10) << (long double) (w * h) / 2.0 << ' ';
    cout << flag << endl;
}
