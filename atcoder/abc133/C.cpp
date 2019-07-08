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
 
void upd(ll &a, ll b) {
    a = (a + b) % mod;
}
 
int main() {
    ll l, r;
    cin >> l >> r;
    ll ans = (l % 2019) * ((l + 1) % 2019) % 2019;
    for(ll i = l ; i <= r ; ++ i) {
        for(ll j = i + 1 ; j <= r ; ++ j) {
            ans = min(ans, (i % 2019) * (j % 2019) % 2019);
            if(!ans) {
                cout << 0 << endl;
                return 0;
            }
        }
    }
    cout << ans << endl;
}
