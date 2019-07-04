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
    ll n, k;
    int tot = 0;
    while(scanf("%lld%lld", &n, &k) == 2) {
        printf("Case #%d: ", ++ tot);
        if(k <= n) {
            printf("%lld\n", k);
        } else {
            k -= n;
            ll blok = k / (n - 1) + (k % (n - 1) != 0);
            ll pos = k % (n - 1);
            if(pos == 0) {
                printf("%lld\n", n - (blok % 2 == 1));
            } else {
                printf("%lld\n", pos);
            }
        }
    }
}
