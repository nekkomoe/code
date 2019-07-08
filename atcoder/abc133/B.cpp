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
 
int n, d;
vector<vector<ll> > pts;
 
int main() {
    scanf("%d%d", &n, &d);
    for(int i = 0 ; i < n ; ++ i) {
        vector<ll> p;
        for(int j = 0, x ; j < d ; ++ j) {
            scanf("%d", &x);
            p.push_back(x);
        }
        pts.push_back(p);
    }
    int ans = 0;
    for(int i = 0 ; i < pts.size() ; ++ i) {
        for(int j = i + 1 ; j < pts.size() ; ++ j) {
            ll s = 0;
            for(int k = 0 ; k < d ; ++ k) {
                ll t = (pts[i][k] - pts[j][k]);
                s += t * t;
            }
            ll tmp = sqrt(s);
            if(tmp * tmp == s) {
                ++ ans;
            }
        }
    }
    printf("%d\n", ans);
}
