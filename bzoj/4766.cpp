#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

const int N = 5e5 + 10;

ll n, m, p;

ll mul(ll a, ll b) {
    a %= p;
    ll r = 0;
    for( ; b ; b >>= 1, a = (a + a) % p) {
        if(b & 1) {
            r = (r + a) % p;
        }
    }
    return r;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = mul(a, a)) {
        if(b & 1) {
            r = mul(r, a);
        }
    }
    return r % p;
}

int main() {
    scanf("%lld%lld%lld", &n, &m, &p);
    ll ans = mul(pw(n, m - 1), pw(m, n - 1));
    printf("%lld\n", (ans % p + p) % p);
}

