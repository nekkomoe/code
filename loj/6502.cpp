#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 2010;

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
int n, m, w[N];
ll f[N][N], g[N][N];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &w[i]);
    }
    sort(w + 1, w + 1 + n);
    deque<int> dq;
    int l = 1, r = n;
    while(l <= r) {
        if(w[l] + w[r] >= m) {
            dq.push_front(w[r]);
            -- r;
        } else {
            dq.push_front(w[l]);
            ++ l;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        w[i] = dq.front(); dq.pop_front();
    }
    memset(f, 0xcf, sizeof f);
    f[1][0] = 0, g[1][0] = 1;
    f[1][1] = 0, g[1][1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        f[i][0] = f[i - 1][0];
        g[i][0] = g[i - 1][0];
        for(int j = 1 ; j <= i ; ++ j) {
            if(w[i] + w[1] >= m) {
                f[i][j] = f[i - 1][j - 1] + i - j;
                g[i][j] = g[i - 1][j - 1];

                ll val = f[i - 1][j] + j;
                if(val > f[i][j]) {
                    f[i][j] = val;
                    g[i][j] = g[i - 1][j];
                } else if(val == f[i][j]) {
                    (g[i][j] += g[i - 1][j]) %= mod;
                }
            } else {
                f[i][j] = f[i - 1][j - 1];
                g[i][j] = g[i - 1][j - 1];

                ll val = f[i - 1][j];
                if(val > f[i][j]) {
                    f[i][j] = val;
                    g[i][j] = g[i - 1][j];
                } else if(val == f[i][j]) {
                    (g[i][j] += g[i - 1][j]) %= mod;
                }
            }
            // printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
        }
    }
    ll mx = -1, cnt = 0;
    for(int i = 0 ; i <= n ; ++ i) {
        if(f[n][i] > mx) {
            mx = f[n][i];
            cnt = g[n][i];
        } else if(f[n][i] == mx) {
            (cnt += g[n][i]) %= mod;
        }
    }
    printf("%lld %lld\n", mx, cnt);
}
