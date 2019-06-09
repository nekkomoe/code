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
 
int n, m;
int ban[N];
ll f[N];
 
int main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x; cin >> x;
        ban[x] = 1;
    }
    f[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        if(ban[i]) continue;
        for(int j = 1 ; j <= 2 ; ++ j) {
            if(i - j >= 0) {
                f[i] = (f[i] + f[i - j]) % mod;
            }
        }
    }
    cout << f[n] << endl;
}
