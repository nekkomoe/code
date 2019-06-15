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

ll f(ll n) {
    ll r = 0;
    while(n) {
        r += n % 10;
        n /= 10;
    }
    return r;
}

int main() {
    // for(int i = 1 ; i <= 1000000 ; ++ i) {
    //     if(i / 2 == f(i)) {
    //         printf("%lld\n", i);
    //     }
    // }
    int q; ll n;
    scanf("%d", &q);
    while(q --) {
        scanf("%lld", &n);
        printf("%d\n", (n % 17 == 0) + (n % 18 == 0));
    }
}
