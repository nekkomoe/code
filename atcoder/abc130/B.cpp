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
 
ll n, x, l[N];
 
int main() {
    ll d = 0;
    cin >> n >> x;
    int ans = d <= x;
    for(int i = 1 ; i <= n ; ++ i) {
        int y; cin >> y;
        d += y;
        ans += d <= x;
    }
    cout << ans << endl;
}
