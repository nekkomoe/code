#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

ll fac[N], invfac[N], inv[N], q[N], q_minus[N], q_inv[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) fac[i] = fac[i - 1] * i % mod;
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) invfac[i] = invfac[i + 1] * (i + 1) % mod;
    inv[0] = 1; for(int i = 1 ; i <= n ; ++ i) inv[i] = pw(i, mod - 2);
    q[0] = q_minus[0] = q_inv[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        q[i] = q[i - 1] * 26 % mod;
        q_minus[i] = q_minus[i - 1] * 25 % mod;
        q_inv[i] = q_inv[i - 1] * pw(26, mod - 2) % mod;
    }
}

ll C(int n, int m) {
    return m < 0 || n < m ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

int n, m;
char s[N];

struct ASK { int len, n, id; } ask[N];
bool cmp(ASK a, ASK b) {
    return a.len < b.len;
}
int tot;
ll ans[N], a[N];

int main() {

    init(N - 1);

    scanf("%d%s", &m, s + 1);
    int len = strlen(s + 1);
    while(m --) {
        int op; scanf("%d", &op);
        if(op == 1) {
            scanf("%s", s + 1);
            len = strlen(s + 1);
        } else {
            scanf("%d", &n);
            ++ tot;
            ask[tot] = (ASK) { len, n, tot };
        }
    }
    sort(ask + 1, ask + 1 + tot, cmp);

    for(int i = 1 ; i <= tot ; ++ i) {
        int len = ask[i].len, n = ask[i].n;
        if(len != ask[i - 1].len) {
            memset(a, 0, sizeof(a[0]) * len);
            for(int j = len ; j < N ; ++ j) {
                a[j] = (a[j - 1] + q_minus[j - len] * q_inv[j] % mod * C(j - 1, len - 1)) % mod;
            }
        }
        ans[ask[i].id] = q[n] * a[n] % mod;
    }

    for(int i = 1 ; i <= tot ; ++ i) {
        printf("%lld\n", (ans[i] % mod + mod) % mod);
    }
}
