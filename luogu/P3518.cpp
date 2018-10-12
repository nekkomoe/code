// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std; typedef long long ll;
const int N = 3e5 + 10;

ll n, a[N]; int k;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll s[N]; int tot;

int main() {
    scanf("%lld%d", &n, &k);
    for(int i = 1 ; i <= k ; ++ i) scanf("%lld", &a[i]);
    ll d = gcd(a[k], n);
    for(ll i = 1 ; i * i <= d ; ++ i) {
        if(d % i == 0) {
            s[++ tot] = i;
            if(i != d / i) {
                s[++ tot] = d / i;
            }
        }
    }
    sort(s + 1, s + 1 + tot);
    for(int i = 1 ; i <= tot ; ++ i) {
        ll d = s[i];
        int f = 1;
        for(int j = 1 ; j <= k - 1 ; ++ j)
            if(a[j] % d == 0) {
                f = 0;
                break;
            }
        if(f) printf("%lld\n", n / d), exit(0);
    }
    puts("fafa");
}
