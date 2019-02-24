#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 9999991;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int main() {
    ll ans = 1, n; cin >> n;
    for(int i = 1 ; i <= n - 1 ; ++ i) ans = ans * i % mod;
    if(n >= 2) ans = ans * pw(n, n - 2) % mod;
    cout << ans << endl;
}
