#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
 
int n;
 
ll ans, fac[(int) 2e6 + 10];
 
const int p = 998244353;
 
ll pw(ll a, int b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % p) if(b & 1) r = r * a % p;
    return r;
}
 
ll inv(ll a) {
    return pw(a, p - 2);
}
 
int main() {
    cin >> n;
    for(int i = fac[0] = 1 ; i <= 2 * n ; ++ i) fac[i] = fac[i - 1] * i % p;
    for(int i = 1 ; i <= n ; ++ i) {
        ans = (ans + fac[2 * i] * inv(fac[i]) % p * inv(fac[i]) % p) % p;
    }
    cout << ans << endl;
}
