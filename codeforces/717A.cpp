// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, inv10 = 700000005, inv2 = 500000004, inv6 = 166666668;

ll S[1100][1100], C[1100][1100], fac[1100], invfac[1100];
int type;

ll pw(ll a, ll b) {
    ll r = 1;
    for(a %= mod ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

ll inv(ll n) { return pw(n, mod - 2); }
struct Z_R { ll a, b, nek; };
const Z_R
        f_a = (Z_R) { inv10, inv2, 5 },
        f_x0 = (Z_R) { inv2, inv2, 5 },
        f_b = (Z_R) { -inv10, inv2, 5 },
        f_x1 = (Z_R) { -inv2, inv2, 5 },
        g_a = (Z_R) { inv6, inv2, 3 },
        g_x0 = (Z_R) { 1, 2, 3 },
        g_b = (Z_R) { -inv6, inv2, 3 },
        g_x1 = (Z_R) { -1, 2, 3 };

Z_R operator + (Z_R x, Z_R y) { return (Z_R) { (x.a + y.a) % mod, (x.b + y.b) % mod, x.nek }; }
Z_R operator - (Z_R x, Z_R y) { return (Z_R) { (x.a - y.a) % mod, (x.b - y.b) % mod, x.nek }; }
Z_R operator * (Z_R x, Z_R y) { return (Z_R) { (x.a * y.b % mod + x.b * y.a % mod) % mod, (x.nek * x.a * y.a % mod + x.b * y.b % mod) % mod, x.nek }; }

Z_R inv(Z_R x) {
    ll a = x.a, b = x.b, dn = inv(x.nek * a * a % mod - b * b % mod);
    return (Z_R) { a * dn % mod, -b * dn % mod};
}

Z_R pw(Z_R a, ll b) {
    Z_R r = (Z_R) { 0, 1, a.nek };
    for( ; b ; b >>= 1, a = a * a)
        if(b & 1)
            r = r * a;
    return r;
}

Z_R getsum(Z_R a, ll n) {
    if(n <= 0) return (Z_R) { 0, 0, a.nek };
    if(a.a == 0 && a.b == 1) return (Z_R) { 0, n % mod, a.nek };
    return (pw(a, n + 1) - a) * inv(a - (Z_R) { 0, 1, a.nek });
}

ll get_f_sum(ll l, ll r, ll k) {
    if(k == 0) return (r - l + 1) % mod;
    Z_R res = (Z_R) { 0, 0, 5 };
    for(int j = 0 ; j <= k ; ++ j) {
        Z_R tmp = getsum(pw(f_x0, j) * pw(f_x1, k - j), r);
        if(l > 1) {
            tmp = tmp - getsum(pw(f_x0, j) * pw(f_x1, k - j), l - 1);
        }
        res = res + (Z_R) { 0, C[k][j], 5 } * pw(f_a, j) * pw(f_b, k - j) * tmp;
    }
    return res.b;
}

ll get_h_sum(ll n, ll k) {
    if(n <= 0) return 0;
    if(k == 0) return n % mod;
    Z_R res = (Z_R) { 0, 0, 3 };
    for(int j = 0 ; j <= k ; ++ j) {
        res = res + (Z_R) { 0, C[k][j], 3 } * pw(g_a, j) * pw(g_b, k - j) * getsum(pw(g_x0, j) * pw(g_x1, k - j), n);
    }
    return res.b;
}

ll get_g_sum(ll l, ll r, ll k) { return get_h_sum(r / 2, k) - get_h_sum((l - 1) / 2, k); }

void init() {
    int n = 1000;
    fac[0] = 1, invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    C[0][0] = S[0][0] = 1;
    for(int i = 1 ; (C[i][0] = 1), i <= n ; ++ i)
        for(int j = 1 ; j <= i ; ++ j)
            S[i][j] = ((i - 1) * S[i - 1][j] + S[i - 1][j - 1]) % mod,
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
}

void runprog() {
    ll l, r, k, ans = 0; scanf("%lld%lld%lld", &k, &l, &r);
    ++ l, ++ r;
    for(int j = 0 ; j <= k ; ++ j)
        if(type == 2) ans = (ans + get_f_sum(l, r, j) * S[k][j] * ((k - j) & 1 ? -1 : 1) % mod) % mod;
        else ans = (ans + get_g_sum(l, r, j) * S[k][j] * ((k - j) & 1 ? -1 : 1) % mod) % mod;
    printf("%lld\n", (ans % mod * invfac[k] % mod + mod) % mod);
}

int main() {

    // cout << inv(10) << ' ' << inv(2) << ' ' << inv(6) << endl;

    init();
    type = 2;
    runprog();
    // init(); int t; scanf("%d%d", &t, &type);
    // while(t --) { runprog(); }
}
