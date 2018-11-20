// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long lon; 
typedef __int128 ll;

ll k, m;

ll pw(ll a, ll b) {
    ll r = 1;
    a %= m;
    for( ; b ; b >>= 1, a = a * a % m)
        if(b & 1)
            r = r * a % m;
    return r % m;
}

map<ll, ll> hs;

int main() {
    lon _k, _m; cin >> _k >> _m; k = _k, m = _m;
    k = ((9 * k % m + 1) % m + m) % m;
    if(10 % m == 0) {
        puts("0"); // fafa
        return 0;
    }
    ll len = 0; while(len * len <= m) ++ len;
    ll tenL = pw(10, len); 
    for(ll i = 0, pro = 1 % m ; i <= len ; ++ i) {
        if(hs.find(pro) == hs.end()) hs[pro] = i;
        pro = pro * tenL % m;
    }
    
//    for(auto t: hs) {
//        printf("%lld: %lld\n", (lon) t.first, (lon) t.second);
//    }
    
    ll ans = -1;
    for(ll y = 0, ypw = 1 ; y <= len ; ++ y) {
        ll xmi = k * ypw % m;
        if(hs.find(xmi) != hs.end()) {
            ll res = hs[xmi] * len - y;
            if(res >= 0 && (ans == -1 || res < ans)) ans = res;
        }
        ypw = ypw * 10 % m;
    }
    printf("%lld\n", (lon) ans);
} 

