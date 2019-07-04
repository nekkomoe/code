#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 2e5 + 10;

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

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n;
ll l[N], r[N], s[N], p[N], q[N];

ll P_SAME(int i) {
    ll len = min(r[i - 1], min(r[i], r[i + 1])) - max(l[i - 1], max(l[i], l[i + 1]));
    if(len >= 0) {
        return len * getinv(
              (r[i - 1] - l[i - 1])
            * (r[i] - l[i]) % mod
            * (r[i + 1] - l[i + 1]) % mod
            ) % mod;
    } else {
        return 0;
    }
}

ll E(int i) {
    return (1 - q[i] - q[i + 1] + P_SAME(i)) % mod;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &l[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &r[i]);
        ++ r[i];
    }
    ll ans = 0, s = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        if(min(r[i - 1], r[i]) - max(l[i - 1], l[i]) >= 0) {
            q[i] =
               (min(r[i - 1], r[i]) - max(l[i - 1], l[i]))
              * getinv((r[i] - l[i]) * (r[i - 1] - l[i - 1]) % mod);
        }
        p[i] = (1 - q[i]) % mod;
        upd(s, p[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        upd(ans, p[i]);
        ll pro = s;
        for(int j = max(1, i - 1) ; j <= min(n, i + 1) ; ++ j) {
            upd(pro, -p[j]);
        }
        upd(ans, p[i] * pro % mod);
        if(i - 1 >= 1) {
            upd(ans, E(i - 1));
        }
        if(i + 1 <= n) {
            upd(ans, E(i));
        }
    }
    printf("%lld\n", (ans % mod + mod) % mod);
}
