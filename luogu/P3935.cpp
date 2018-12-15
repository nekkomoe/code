#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353; 

ll sol(ll n) { 
    if(n <= 0) return 0;
    ll ans = 0;
    for(ll i = 1, j ; i <= n ; i = j + 1) j = n / (n / i), ans += (j - i + 1) % mod * ((n / i) % mod) % mod;
    return ans;
}

int main() {
    ll l, r; cin >> l >> r;
    ll ans = sol(r) - sol(l - 1);
    cout << (ans % mod + mod) % mod << endl;

}

