#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll getxor(ll n) {
    if(n <= 0) return 0;
    ll res = 0;
//    for(ll i = 1 ; i <= n ; ++ i) res ^= i;
    if(n % 2 == 1) {
        res = ((n + 1) / 2) % 2 == 1 ? 1 : 0;
    } else {
        res = n ^ getxor(n - 1);
    }
    return res;
}

int main() {
    
//    for(int i = 1 ; i <= 10 ; ++ i) cout << getxor(i) << ' '; cout << endl;
    
    int n; scanf("%d", &n);
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ll x, m; scanf("%lld%lld", &x, &m);
        ans ^= getxor(x + m - 1) ^ getxor(x - 1);
    }
    puts(ans ? "tolik" : "bolik");
}

