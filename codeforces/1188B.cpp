#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 3e5 + 10;
int n, mod, k;
ll a[N];
 
int main() {
    scanf("%d%d%d", &n, &mod, &k);
    map<ll, ll> tmp;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        ll x = a[i] % mod;
        ll y = (x * x % mod * x % mod * x % mod - (ll) k * x % mod) % mod;
        y = (y % mod + mod) % mod;
        tmp[y] ++;
    }
    ll res = 0;
    for(auto t: tmp) {
        res += (ll) t.second * (t.second - 1) / 2;
    }
    printf("%lld\n", res);
}
