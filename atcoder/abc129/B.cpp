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
 
ll n, a[N];
 
int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
    }
    ll ans = -1;
    for(int i = 1 ; i < n ; ++ i) {
        ll x = 0, y = 0;
        for(int j = 1 ; j <= i ; ++ j) {
            x += a[j];
        }
        for(int j = i + 1 ; j <= n ; ++ j) {
            y += a[j];
        }
        if(ans == -1) ans = abs(x - y);
        else ans = min(ans, abs(x - y));
    }
    cout << ans << endl;
}
