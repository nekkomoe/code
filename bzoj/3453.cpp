#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int T = 200, N = T + 10;
const ll mod = 1234567891ll;

ll k, a, n, d;
ll fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll pre[N], sub[N];
ll lagerangri_fafa(ll *f, ll n, ll k) {
    ll res = 0;
    pre[0] = sub[0] = 1;
    for(int i = 1 ; i <= k ; ++ i) {
        pre[i] = pre[i - 1] * (n - i) % mod;
        sub[i] = sub[i - 1] * (n - k + i - 1) % mod;
    }
    for(int i = 1 ; i <= k ; ++ i) {
        ll x = pre[i - 1] * sub[k - i] % mod * f[i] % mod;
        ll y = invfac[i - 1] * invfac[k - i] % mod;
        res = (res + x * y % mod * ((k - i) & 1 ? -1 : 1)) % mod;
    } 
    return res;
}

ll f[N], g[N];

void sol() {
    cin >> k >> a >> n >> d;
    for(int i = 0 ; i <= k + 3 ; ++ i) g[i] = pw(i, k);
    for(int i = 1 ; i <= k + 3 ; ++ i) g[i] = (g[i - 1] + g[i]) % mod; 
    for(int i = 1 ; i <= k + 3 ; ++ i) g[i] = (g[i - 1] + g[i]) % mod;
    for(int i = 0 ; i <= k + 5 ; ++ i) {
        if(i) f[i] = f[i - 1];
        else f[i] = 0;
        f[i] = (f[i] + lagerangri_fafa(g, (a + i * d % mod) % mod, k + 3)) % mod;
    }
    ll ans = lagerangri_fafa(f, n, k + 5);
    cout << (ans % mod + mod) % mod << endl;
}

int main() {
	ios :: sync_with_stdio(0);
	fac[0] = invfac[0] = 1;
	for(int i = 1 ; i <= T ; ++ i) fac[i] = fac[i - 1] * i % mod;
	invfac[T] = pw(fac[T], mod - 2);
	for(int i = T - 1 ; i >= 1 ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    int t; cin >> t;
    while(t --) sol();
}

