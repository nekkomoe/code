#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10, mod = 998244353;
const int T = 10000;
int n, m, a[N], b[N];

vector<int> num, posA[N], posB[N]; int num_sz;
void re_label() {
    for(int i = 0 ; i <= n ; ++ i) num.push_back(a[i]);
    for(int i = 0 ; i <= m ; ++ i) num.push_back(b[i]);
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 0 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
        posA[a[i]].push_back(i);
    }
    for(int i = 0 ; i <= m ; ++ i) {
        b[i] = lower_bound(num.begin(), num.end(), b[i]) - num.begin() + 1;
        posB[b[i]].push_back(i);
    }
    num_sz = num.size();
}

int cnt[N]; ll ans[N];

void go_force(int val) {
    for(int pa: posA[val]) {
        for(int pb: posB[val]) {
            (ans[pa + pb] += (ll) pa * pb % mod) %= mod;
        }
    }
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod)
        if(b & 1)
            r = r * a % mod;
    return r;
}

const ll g[2] = { 3, pw(3, mod - 2) };

int rev(int x, int n) {
    int res = 0;
    for(int i = 0 ; (1 << i) < n ; ++ i)
        res = (res << 1) | ((x >> i) & 1);
    return res;
}

ll f[N];

void ntt(ll *a, int flag, int n) {
    for(int i = 0 ; i < n ; ++ i) f[rev(i, n)] = a[i];

    for(int i = 2 ; i <= n ; i <<= 1) {
        ll wn = pw(g[flag], (mod - 1) / i);
        for(int j = 0 ; j < n ; j += i) {
            ll w = 1;
            for(int k = j ; k < j + i / 2 ; ++ k) {
                ll u = f[k], v = w * f[k + i / 2] % mod;
                f[k] = (u + v) % mod;
                f[k + i / 2] = (u - v) % mod;
                w = w * wn % mod;
            }
        }
    }

    for(int i = 0, inv = pw(n, mod - 2) ; i < n ; ++ i) {
        a[i] = f[i];
        if(flag) {
            a[i] = a[i] * inv % mod;
        }
    }
}

ll ua[N], ub[N]; int len;

void go_ntt(int val) {
    for(int i = 0 ; i < len ; ++ i) ua[i] = ub[i] = 0;

    for(int pa: posA[val]) {
        ua[pa] = pa;
    }
    for(int pb: posB[val]) {
        ub[pb] = pb;
    }
    ntt(ua, 0, len), ntt(ub, 0, len);
    for(int i = 0 ; i < len ; ++ i) ua[i] = ua[i] * ub[i] % mod;
    ntt(ua, 1, len);
    for(int i = 0 ; i <= n + m ; ++ i) {
        (ans[i] += ua[i]) %= mod;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 0 ; i <= m ; ++ i) scanf("%d", &b[i]);
    re_label();
    len = 1;
    while(len <= n + m + 5) len <<= 1;
    for(int i = 0 ; i <= n ; ++ i) ++ cnt[a[i]];
    for(int i = 0 ; i <= m ; ++ i) ++ cnt[b[i]];
    for(int i = 1 ; i <= num_sz ; ++ i) {
        if(cnt[i] <= T) {
            // force
            go_force(i);
        } else {
            // ntt
            go_ntt(i);
        }
    }
    for(int i = 0 ; i <= n + m ; ++ i) {
        printf("%lld ", (ans[i] + mod) % mod);
    }
}
