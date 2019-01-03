#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = (1ll << 20) + 10;
int n; ll a[N];

class Nim {
public:
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod)
            if(b & 1)
                r = r * a % mod;
        return r;
    }
    const ll inv2 = pw(2, mod - 2);
    void fwt(int ty) {
        for(int i = 2 ; i <= n ; i <<= 1) {
            for(int j = 0 ; j + i / 2 < n ; j += i) {
                for(int k = j ; k < j + i / 2 ; ++ k) {
                    ll u = a[k], v = a[k + i / 2];
                    if(ty == 0) a[k] = (u + v) % mod, a[k + i / 2] = (u - v) % mod;
                    else a[k] = (u + v) * inv2 % mod, a[k + i / 2] = (u - v) * inv2 % mod;
                }
            }
        }
    }
    ll count(int k, int n) {
        memset(a, 0, sizeof a);
        for(int i = 2 ; i <= n ; ++ i)
            if(!a[i])
                for(int j = i + i; j <= n ; j += i)
                    a[j] = 1;
        for(int i = 2 ; i <= n ; ++ i) a[i] ^= 1;
        :: n = n = 1 << 20;
        fwt(0);
        
//        cout << inv2 << endl;
//        for(int i = 0 ; i < 10 ; ++ i) cout << a[i] << ' ';
//        cout << endl;
        
        for(int i = 0 ; i < n ; ++ i) a[i] = pw(a[i], k);
        fwt(1);
        return (a[0] % mod + mod) % mod;
    }
};

#ifdef fafa
int main() {
	ios :: sync_with_stdio(0);
    Nim test;
    int k, n; cin >> k >> n;
    cout << test.count(k, n) << endl;
}
#endif

