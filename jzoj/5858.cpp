#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, T = 2e5, mod = 998244353;
int fac[N], invfac[N];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll h[N], f[N], g[N]; int n, m, k;

int pri[N], tot, use[N], cnt; bool vis[N];

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : (ll) fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

namespace NTT {
	const int N = 4e5 + 10;
	const ll p = 998244353ll, g[2] = {3, 332748118};

	ll pw(ll a, ll b) {
	    ll res = 1;
	    while(b) {
	        if(b & 1) res = res * a % p;
	        b >>= 1, a = a * a % p;
	    }
	    return res;
	}
	
	int n, m, len;
	
	ll a[N], b[N], f[N], inv;
	
	int rev(int x, int n) {
	    int res = 0;
	    for(int i = 0 ; (1 << i) < n ; ++ i) (res <<= 1) |= (x >> i) & 1;
	    return res;
	}
	
	void ntt(ll *t, int n, int ty) {
	    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = t[i];
	
	    for(int i = 2 ; i <= n ; i <<= 1) {
	        ll wn = pw(g[ty], (p - 1) / i);
	        for(int j = 0 ; j < n ; j += i) {
	            ll w = 1;
	            for(int k = j ; k < j + i / 2 ; ++ k) {
	                ll u = f[k], v = w * f[k + i / 2] % p;
	                f[k] = (u + v) % p;
	                f[k + i / 2] = ((u - v) % p + p) % p;
	                w = w * wn % p;
	            }
	        }
	    }
	
	    if(ty) for(int i = 0 ; i < n ; ++ i) t[i] = f[i] * inv % p;
	    else for(int i = 0 ; i < n ; ++ i) t[i] = f[i];
	}
	
	void sol() {
		n ++, m ++;
	    for(len = 1 ; len <= n + m + 5 ; len <<= 1);
	    inv = pw(len, p - 2);
	    ntt(a, len, 0), ntt(b, len, 0);
	    for(int i = 0 ; i < len ; ++ i) a[i] = a[i] * b[i] % p;
	    ntt(a, len, 1);
	}
};

int main() {
	freopen("h.in", "r", stdin);
    freopen("h.out", "w", stdout);
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= T ; ++ i) fac[i] = (ll) fac[i - 1] * i % mod;
    invfac[T] = pw(fac[T], mod - 2);
    for(int i = T - 1 ; i ; -- i) invfac[i] = (ll) invfac[i + 1] * (i + 1) % mod;
    
    scanf("%d%d%d", &n, &m, &k);
    
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            if(i <= n && k - i >= 0) use[++ cnt] = i;
        }
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
        }
    }
    
    for(int i = 0 ; i <= T ; ++ i)
		if(k - i >= 2 && k - i <= k && !vis[k - i])
			f[i] = C(n, k - i) * invfac[i] % mod; 
    
	for(int i = 0 ; i <= m ; ++ i) g[i] = invfac[i];
    
    NTT :: n = m + 1, NTT :: m = m + 1;
    for(int i = 0 ; i <= m ; ++ i) NTT :: a[i] = f[i];
    for(int i = 0 ; i <= m ; ++ i) NTT :: b[i] = g[i];
    NTT :: sol();
    
    for(int i = 0 ; i <= m ; ++ i) h[i] = NTT :: a[i];
    
    
    for(int i = 0 ; i <= m ; ++ i) {
        h[i] = h[i] * fac[i] % mod * pw(C(n + i, k), mod - 2) % mod;
        printf("%lld\n", (h[i] % mod + mod) % mod);
    }
    
}
