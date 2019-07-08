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
 
int n, q;
ll a[N];
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        a[i] += a[i - 1];
    }
    scanf("%d", &q);
    while(q --) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%lld\n", (a[r] - a[l - 1]) / 10);
    }
}
