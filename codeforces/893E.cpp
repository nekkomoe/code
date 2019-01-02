#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T = 2e6, N = T + 10, mod = 1e9 + 7; 

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll fac[N], invfac[N];

ll C(int n, int m) {
    return n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

void sol() {
    ll x, y; cin >> x >> y;
    ll prod = pw(2, y - 1);
    
    for(ll i = 2 ; i * i <= x ; ++ i) {
        if(x % i == 0) {
            ll cnt = 0;
            while(x % i == 0) x /= i, ++ cnt;
            prod = prod * C(y + cnt - 1, cnt) % mod;
        }
    }
    if(x > 1) {
        prod = prod * y % mod;
    }
    
    cout << (prod % mod + mod) % mod << endl;
}

int main() {
//    freopen("data.in", "r", stdin);
	ios :: sync_with_stdio(0);
	fac[0] = invfac[0] = 1;
	for(int i = 1 ; i <= T ; ++ i) fac[i] = fac[i - 1] * i % mod;
	invfac[T] = pw(fac[T], mod - 2);
	for(int i = T - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    int q; cin >> q; while(q --) sol();
}

