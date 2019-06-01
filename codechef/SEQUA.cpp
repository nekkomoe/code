#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, mod, ans;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

ll calc(ll n, ll q) {
    // 1 + q + q^2 + ... + q^n
    // ll r = 0, prod = 1;
    // for(ll i = 0 ; i <= n ; ++ i) {
    //     upd(r, prod);
    //     prod = prod * q % mod;
    // }
    // return r;

    // cout << n << ' ' << q << endl;

    if(n == 0) {
        return 1;
    } else if(n & 1) {
        return (pw(q, (n + 1) / 2) + 1) * calc(n / 2, q) % mod;
    } else {
        return (pw(q, n) + calc(n - 1, q)) % mod;
    }
}

void runprog() {
    scanf("%lld%lld", &n, &mod);
    if(n < mod) {
        ans = 0;
        for(ll i = 0 ; i <= n ; ++ i) {
            upd(ans, pw(i, i));
        }
    } else {
        ans = 1;
        for(ll i = 1 ; i < mod ; ++ i) {
            ll cnt = (n - i) / mod;
            ll a = pw(i, i) % mod;
            ll q = pw(i, mod) % mod;
            upd(ans, a * calc(cnt, q) % mod);
        }
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}

signed main() {
    ll t; scanf("%lld", &t);
    while(t --) {
        runprog();
    }
}
