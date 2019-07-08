#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int main() {
    ll r;
    scanf("%lld", &r);
    for(ll x = 1 ; x * x <= r ; ++ x) {
        ll tmp = r - x * x - x - 1;
        // xy=tmp
        if(tmp <= 0 || tmp % 2 || tmp / 2 % x) {
            continue;
        } else {
            printf("%lld %lld\n", x, tmp / 2 / x);
            return 0;
        }
    }
    puts("NO");
}
