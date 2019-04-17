#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 110, K = 1010, mod = 998244353, g = 3;

inline ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
inline void upd(ll &x, ll y) {
    x = (x + y) % mod;
}

int n, k;
ll f[K], A[N], B[N], C[N], mx, ans;

namespace CALC_EQU {
    #define ll __int128
    ll f(ll a, ll b, ll c, ll n) {
        if(n <= 0) return 0;
        return n * (n - 1) / 2 * (a / c) + n * (b / c) + f(c, (a * n + b) % c, a % c, (a % c * n + b % c) / c);
    }

    // sum_{i=0}^{n-1} [(ax+b)/c % d <= t]
    ll calc_sub(ll a, ll b, ll c, ll n, ll d, ll t) {
        if(t < 0) return 0;
        ll res = 0;
        res += f(a, b, c * d, n + 1);
        ll tmp = b - c * (t + 1);
        if(tmp >= 0) {
            res -= f(a, tmp, c * d, n + 1);
        } else {
            ll k = ceil(1.0 * -tmp / c);
            res -= f(a, tmp + k * (c * d), c * d, n + 1) - k * (n + 1);
        }
        return res;
    }

    // sum_{i=0}^{n-1} [(ax+b)/c % mod = tar]
    ll calc(ll a, ll b, ll c ,ll n, ll t_mod, ll tar) {
        return calc_sub(a, b, c, n, t_mod, tar) - calc_sub(a, b, c, n, t_mod, tar - 1);
    }

    #undef ll
}

int main() {
// #ifdef ONLINE_JUDGE
//     freopen("pressure.in", "r", stdin);
//     freopen("pressure.out", "w", stdout);
// #endif
    scanf("%d%d", &n, &k);
    if(k == 1) {
        puts("0");
        return 0;
    }
    for(int i = 0 ; i < k ; ++ i) {
        scanf("%lld", &f[i]);
    }
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld%lld%lld", &A[i], &B[i], &C[i]);
        mx = max(mx, A[i] * B[i] + C[i]);
    }

    __int128 prod = 1;
    for(ll bit = 0 ; prod <= mx && bit <= 60 ; ++ bit, prod = prod * k) {
        vector<vector<ll> > pak(n);
        for(int i = 0 ; i < n ; ++ i) {
            pak[i].resize(k);
            for(int j = 0 ; j < k ; ++ j) {
                pak[i][j] = CALC_EQU :: calc(B[i], C[i], prod, A[i], k, j);
            }
        }
        vector<ll> res(k);
        res[0] = 1;
        for(int i = 0 ; i < n ; ++ i) {
            vector<ll> tmp(k), bak;
            bak = res;
            for(int j = 1 ; j < k ; ++ j) {
                upd(bak[j], bak[j - 1]);
            }
            for(int j = 0 ; j < k ; ++ j) {
                upd(tmp[j], bak[j] * pak[i][j] % mod);
            }
            for(int j = 1 ; j < k ; ++ j) {
                upd(tmp[j], res[j] * pak[i][j - 1] % mod);
                upd(pak[i][j], pak[i][j - 1]);
            }
            res = tmp;
        }
        for(int i = 0 ; i < k ; ++ i) {
            upd(ans, f[i] * res[i] % mod);
        }
    }

    ans = (ans % mod + mod) % mod;
    printf("%lld\n", ans);
}
