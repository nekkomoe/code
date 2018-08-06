#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int p = 19940417;

ll n, m;

ll g(ll k) {
    ll r = 0;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        if(k / i == 0) break;
        j = min(n, k / (k / i));
        r = (r + (i + j) * (j - i + 1) / 2 % p * (k / i) % p) % p;
    }
    return r;
}

ll f(ll n) {
    ll r = 0;
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        r = (r + (i + j) * (j - i + 1) / 2 % p * (n / i)) % p;
    }
    return (n * n % p - r % p) % p;
}

ll sum(ll n) {
    return n * (n + 1) % p * (2 * n + 1) % p * 3323403 % p;
}

ll w() {
    ll r = 0;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        if(n / i == 0 || m / i == 0) break;
        j = min(n / (n / i), m / (m / i));
        r = (r + (sum(j) - sum(i - 1)) % p * (n / i) % p * (m / i) % p) % p;
    }
    return r;
}

int main() {
    scanf("%lld%lld", &n, &m); if(n > m) swap(n, m);
    ll ans = f(n) * f(m) % p + m * g(n) % p + n * g(m) % p - n * n % p * m % p - w() % p;
    printf("%lld\n", (ans % p + p) % p);
}
