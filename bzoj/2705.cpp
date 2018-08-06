#include <bits/stdc++.h>

using namespace std;

using namespace std;

typedef long long ll;

ll n, ans;

ll phi(ll x) {
    ll res = x;
    for(ll i = 2 ; i * i <= x ; ++ i) {
        if(x % i == 0) {
            res = res / i * (i - 1);
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) res = res / x * (x - 1);
    return res;
}

int main() {
    scanf("%lld", &n);
    for(int i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            ans += (ll) i * phi(n / i);
            if(i * i < n) ans += (ll) (n / i) * phi(i);
        }
    }
    printf("%lld\n", ans);
}
