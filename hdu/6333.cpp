#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;

int fac[N], invfac[N];

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

void init() {
    const int n = 1e5;
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = 1ll * fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
}

int C(int n, int m) {
    return n >= m ? 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod : 0;
}

struct Q {
    int n, m, id;
} q[N];
bool operator < (Q a, Q b) {
    int x = a.n / 300, y = b.n / 300;
    return x == y ? a.m < b.m : x < y;
}
int cnt;
ll ans[N];

int main() {
    const ll inv2 = pw(2, mod - 2);
    init();
    scanf("%d", &cnt);
    for(int i = 1 ; i <= cnt ; ++ i)
        scanf("%d%d", &q[i].n, &q[i].m), q[i].id = i;
    sort(q + 1, q + 1 + cnt);
    int n = q[1].n, m = q[1].m;
    ll sum = 0;
    for(int i = 0 ; i <= m ; ++ i) sum = (sum + C(n, i)) % mod;
    ans[q[1].id] = sum;
    for(int i = 2 ; i <= cnt ; ++ i) {
        while(n + 1 <= q[i].n) sum = (2ll * sum - C(n, m)) % mod, ++ n;
        while(m - 1 >= q[i].m) sum = (sum - C(n, m)) % mod, -- m;
        while(n - 1 >= q[i].n) sum = (sum + C(n - 1, m)) % mod * inv2 % mod, -- n;
        while(m + 1 <= q[i].m) sum = (sum + C(n, m + 1)) % mod, ++ m;
        ans[q[i].id] = sum;
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        ll ans = :: ans[i];
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}