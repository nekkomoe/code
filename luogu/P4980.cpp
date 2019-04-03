#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll getphi(ll n) {
    ll r = n;
    for(ll i = 2 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            while(n % i == 0) n /= i;
            r = r / i * (i - 1);
        }
    }
    if(n > 1) r = r / n * (n - 1);
    return r;
}

void runprog() {
    ll n, ans = 0;
    scanf("%lld", &n);
    for(ll i = 1 ; i * i <= n ; ++ i) {
        if(n % i == 0) {
            (ans += pw(n, i) * getphi(n / i) % mod) %= mod;
            if(i != n / i) {
                (ans += pw(n, n / i) * getphi(i) % mod) %= mod;
            }
        }
    }
    (ans *= pw(n, mod - 2)) %= mod;
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
