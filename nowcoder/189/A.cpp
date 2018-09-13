#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll n, k;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}
int main() {
    cin >> n >> k;
    ll cnt = 0;
    for(int i = 1 ; i <= 9 ; ++ i) {
        ll a1 = i;
        ll an = k + a1;
        if(0 <= an && an <= 9) {
            ++ cnt;
        }
    }
    ll ans = cnt * pw(10, n - 2) % mod;
    cout << ans << endl;
}
