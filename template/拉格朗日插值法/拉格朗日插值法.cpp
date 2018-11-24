#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2010, mod = 998244353;
ll n, k, x[N], y[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)   
            r = r * a % mod;
    return r;
}

int main() {
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i) cin >> x[i] >> y[i];
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll pro = 1;
        for(int j = 1 ; j <= n ; ++ j) {
            if(i != j) {
                pro = pro * ((k - x[j]) % mod) % mod * pw(x[i] - x[j], mod - 2) % mod;
            }
        }
        ans = (ans + pro * y[i] % mod) % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}

