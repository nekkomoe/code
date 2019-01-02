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

int n, a[N];

map<int, int> cnt;

void sol() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) cin >> a[i], ++ cnt[a[i]];
    sort(a + 1, a + 1 + n);
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(cnt[a[i]] == 0) continue;
        int x = cnt[a[i]];
        cnt[a[i]] = 0;
        
        if(i + x <= n) {
            ans = (ans + fac[n] * pw(n - i + 1, mod - 2) % mod * x % mod * a[i] % mod) % mod;
//            cout << fac[n] * pw(n - i + 1, mod - 2) % mod * x % mod * a[i] % mod << endl;
        }
    }
    cout << (ans % mod + mod) % mod << endl;
}

int main() {
//    freopen("data.in", "r", stdin);
	ios :: sync_with_stdio(0);
	fac[0] = invfac[0] = 1;
	for(int i = 1 ; i <= T ; ++ i) fac[i] = fac[i - 1] * i % mod;
	invfac[T] = pw(fac[T], mod - 2);
	for(int i = T - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
	sol(); 
}

