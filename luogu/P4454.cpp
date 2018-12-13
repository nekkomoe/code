// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll g, p;

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= p ; b ; b >>= 1, a = a * a % p)
        if(b & 1)
            r = r * a % p;
    return r;
}

void sol() {
    ll A, B, x = 1; cin >> A >> B;
    ll len = ceil(sqrt(p));
    map<ll, ll> f;
    for(ll i = 0 ; i <= len ; ++ i) {
        f[pw(g, i * len)] = i * len;
    }
    for(int i = 0 ; i <= len ; ++ i) {
        ll val = A * pw(g, i) % p;
        if(f.count(val)) {
            ll t = f[val];
            if(t >= i) {
                x = t - i;
                break;
            }
        }
    }
    cout << (pw(B, x) % p + p) % p << endl;
}

int main() {
    ios :: sync_with_stdio(0);
    cin >> g >> p;
    int t; cin >> t;
    while(t --) sol();
}

