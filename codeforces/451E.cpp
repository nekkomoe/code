#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n;
ll sum, f[21], ans, inv[21];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}

int main() {
    cin >> n >> sum;
    for(int i = 0 ; i < n ; ++ i) cin >> f[i], inv[i] = pw(i, mod - 2);
    for(int s = 0 ; s < (1 << n) ; ++ s) {
        int cnt = 0;
        ll tot = 0;
        for(int i = 0 ; i < n ; ++ i) {
            if((s >> i) & 1) {
                ++ cnt;
                tot += f[i] + 1;
                if(tot > sum) { tot = -1; break; }
            }
        }
        if(tot == -1) continue;
        tot = sum - tot;
        // C(tot + n - 1, n - 1) = (tot + n - 1)! / (n - 1)! / (tot)!
        ll tmp = 1;
        for(ll i = tot + 1 ; i <= tot + n - 1 ; ++ i) (tmp *= i % mod) %= mod;
        for(ll i = 1 ; i <= n - 1 ; ++ i) (tmp *= inv[i] % mod) %= mod;
        if(tmp < 0) cout << "tmp = " << tmp << endl;
        ans = (ans + (cnt & 1 ? -1 : 1) * tmp) % mod;
    }
    ans = (ans % mod + mod) % mod;
    cout << ans << endl;
}
