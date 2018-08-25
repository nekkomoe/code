#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

ll a, b, ans;

set<ll> f;

void sol(ll a, ll b) {
    f.clear();
    ll n = a + b;
    for(ll i = 1 ; i * i <= a ; ++ i) {
        if(a % i) continue;
        f.insert(i), f.insert(a / i);
    }
    for(ll i = 1 ; i * i <= n ; ++ i) {
        if(n % i) continue;
        auto it = f.upper_bound(i);
        if(it != f.begin()) {
            auto x = * -- it;
            auto y = a / x;
            if(y <= n / i) {
                ans = min(ans, 2 * (i + n / i));
            }
        }
    }
}

int main() {
    ans = 0x3f3f3f3f3f3f3f3fll;
    cin >> a >> b;
    sol(a, b);
    sol(b, a);
    cout << ans << endl;
}
