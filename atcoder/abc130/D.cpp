#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int mod = 1e9 + 7, N = 3e5 + 10;
 
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
 
int n, lim;
ll a[N], s[N], k, ans;
vector<ll> num;
 
int main() {
    scanf("%d%lld", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
    }
    // s[i] - s[j] >= k | 0 <= j < i
    // s[i] >= s[j] + k | 0 <= j < i
    num.emplace_back(k);
    for(int i = 1 ; i <= n ; ++ i) {
        if(num.size() && num[0] <= s[i]) {
            ans += upper_bound(num.begin(), num.end(), s[i]) - num.begin();
        }
        num.emplace_back(s[i] + k);
    }
    printf("%lld\n", ans);
}
