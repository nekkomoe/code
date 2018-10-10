// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
ll l1, r1, l2, r2, M;
ll calc(ll n, ll m) {
    ll res = 0;
    for(ll i = 0 ; i <= 62 ; ++ i)
        for(ll j = 0 ; j <= 62 ; ++ j)
            if(((n >> i) & 1) && ((m >> j) & 1)) {
                ll mn = min(i, j), mx = max(i, j);
                ll l = (n - (1ll << i)) ^ (m - (1ll << j));
                l &= ~((1ll << mx) - 1);
                ll r = l + (1ll << mx) - 1;
                ll tmp = (r / M - l / M + (l % M == 0)) % mod;
                res += (1ll << mn) % mod * tmp % mod;
                res %= mod;
            }
    return res;
}

int main() {
 	freopen("mod.in", "r", stdin);
 	freopen("mod.out", "w", stdout);
    cin >> l1 >> r1 >> l2 >> r2 >> M;
    ll ans = (calc(r1 + 1, r2 + 1) - calc(r1 + 1, l2) - calc(l1, r2 + 1) + calc(l1, l2)) % mod;
    ans = (ans % mod + mod) % mod;
    cout << ans << endl;
}
