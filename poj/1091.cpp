#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;

ll n, m;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a *= a) if(b & 1) r *= a;
    return r;
}

const int N = 1e7 + 10;
ll p[N], tot;

int main() {
    cin >> n >> m;
    ll _m = m;
    for(ll i = 2 ; i * i <= _m ; ++ i) {
        if(_m % i) continue;
        p[++ tot] = i;
        while(_m % i == 0) _m /= i;
    }
    if(_m > 1) p[++ tot] = _m;
    ll ans = 0;
    for(int s = 0 ; s < (1 << tot) ; ++ s) {
        ll lcm = 1, cnt = 0;
        for(int i = 1 ; i <= tot ; ++ i) {
            if((s >> (i - 1)) & 1) {
                lcm *= p[i];
                ++ cnt;
            }
        }
        ans += (cnt & 1 ? -1 : 1) * pw(m / lcm, n);
    }
    printf("%lld\n", ans);
}
