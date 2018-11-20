#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int T = 5e6, N = T + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}


// 计算自然数幂和 
ll C[10][10], inv[10];
void initC() {
    C[0][0] = 1;
    for(int i = 1 ; i < 10 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j < 10 ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
        inv[i] = pw(i, mod - 2);
    }
}

ll calcnk(ll n, ll k) {
    static ll S[10];
    S[0] = n + 1;
	ll fafa = (n + 1) % mod;
	for(ll i = 1 ; i <= k ; ++ i) {
		fafa = fafa * ((n + 1) % mod) % mod;
		ll s = fafa;
		for(ll j = 0 ; j < i ; ++ j)
			s = (s - C[i + 1][j] * S[j] % mod) % mod;
		S[i] = inv[i + 1] * s % mod;
	}
	return S[k];
}
// ---------------------------------------------------------------------



ll n, k, ans;

ll phi[N], pri[N], tot, vis[N];

ll ins[N], val[N];
const ll inv2 = pw(2, mod - 2);

map<ll, ll> hs;

ll getsum(ll n) {
    if(n <= T) return phi[n];
    if(ins[:: n / n]) return val[:: n / n]; ins[:: n / n] = 1;
    ll res = (n % mod) * ((n + 1) % mod) % mod * inv2 % mod;
    for(ll i = 2, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        res = (res - (j - i + 1) % mod * getsum(n / i) % mod) % mod;
    }
    return val[:: n / n] = res;
}

int main() {
    initC();
    
    cin >> n >> k; 
    
    phi[1] = 1;
    for(int i = 2 ; i <= T ; ++ i) {
        if(!vis[i]) pri[++ tot] = i, phi[i] = i - 1;
        for(int j = 1 ; j <= tot && i * pri[j] <= T ; ++ j) {
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j] % mod;
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1) % mod;
            }
        }
        phi[i] = (phi[i - 1] + phi[i]) % mod;
    }
    
    for(ll i = 1, j ; i <= n ; i = j + 1) {
        j = n / (n / i);
        ans = (ans + (calcnk(j, k) - calcnk(i - 1, k)) % mod * getsum(n / i) % mod) % mod;
    }
    
    ans = (2 * ans % mod - calcnk(n, k)) % mod;
    if(ans < 0) ans += mod;
    cout << ans << endl;
}

