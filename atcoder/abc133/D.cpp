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
 
int n, a[N], b[N];
 
int main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    ll s = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        cin >> a[i];
        s += a[i];
    }
    ll num = s / 2;
    for(int i = 2 ; i <= n ; i += 2) {
        s -= a[i] << 1;
    }
    cout << s << ' ';
    for(int i = 2 ; i <= n ; ++ i) {
        s = (a[i - 1] << 1) - s;
        cout << s << ' ';
    }
}
