#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 2e6 + 10;

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

ll gause(vector<vector<ll> > a) {
    int n = a.size();

    // for(auto e: a) {
    //     for(auto w: e) {
    //         printf("%lld ", w);
    //     }
    //     puts("");
    // }

    // n * n
    int sig = 0;
    ll res = 1;
    for(int i = 0 ; i < n ; ++ i) {
        if(!a[i][i]) {
            for(int j = i + 1 ; j < n ; ++ j) {
                if(a[j][i]) {
                    for(int k = 0 ; k < n ; ++ k) {
                        swap(a[i][k], a[j][k]);
                    }
                    sig ^= 1;
                    break;
                }
            }
        }
        if(!a[i][i]) {
            return 0;
        }
        res = res * a[i][i] % mod;
        for(int j = 0 ; j < n ; ++ j) {
            if(i != j && a[j][i]) {
                ll pro = mod - a[j][i] * getinv(a[i][i]) % mod;
                for(int k = 0 ; k < n ; ++ k) {
                    upd(a[j][k], a[i][k] * pro % mod);
                }
            }
        }
    }
    return sig ? mod - res : res;
}

ll fac[N], invfac[N];

void init(int n) {
    fac[0] = invfac[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    invfac[n] = pw(fac[n], mod - 2);
    for(int i = n - 1 ; i ; -- i) {
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    }
}

ll C(ll n, ll m) {
    return n < m || m < 0 ? 0 : fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

// ll calc(ll x, ll y, ll a, ll b) {
//     // (x, y) -> (a, b)
//     // 只能往左或者往下
//     x = x - a, y = y - b;
//     return C(x + y, x);
// }

int n, m;
char mp[3010][3010];
ll f[3010][3010];
ll calc(int sx, int sy, int tx, int ty) {
    if(1 <= sx && sx <= n && 1 <= sy && sy <= m
    && 1 <= tx && tx <= n && 1 <= ty && ty <= m
    && mp[sx][sy] == '.'
    && mp[tx][ty] == '.') {
        memset(f, 0, sizeof f);
        f[sx][sy] = 1;
        for(int i = sx ; i <= tx ; ++ i) {
            for(int j = sy ; j <= ty ; ++ j) {
                if(mp[i][j] == '#') {
                    f[i][j] = 0;
                }
                upd(f[i + 1][j], f[i][j]);
                upd(f[i][j + 1], f[i][j]);
            }
        }
        return f[tx][ty];
    } else {
        return 0;
    }
}

int main() {
    // init(N - 1);
    // ll a, b, c;
    // cin >> a >> b >> c;
    // vector<vector<ll> > A(c, vector<ll> (c));
    // for(int i = 1 ; i <= c ; ++ i) {
    //     for(int j = 1 ; j <= c ; ++ j) {
    //         A[i - 1][j - 1] = calc(a + i - 1, b - i + 1, j - 1, -j + 1);
    //     }
    // }
    // ll ans = gause(A);
    // cout << ans << endl;
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", mp[i] + 1);
    }
    vector<vector<ll> > A(2, vector<ll> (2));
    int S[2][2] = { {2, 1}, {1, 2} };
    int T[2][2] = { {n, m - 1}, {n - 1, m} };
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            A[i][j] = calc(S[i][0], S[i][1], T[j][0], T[j][1]);
            // printf("ways: (%d, %d) -> (%d, %d) = %lld\n", S[i][0], S[i][1], T[j][0], T[j][1], A[i][j]);
        }
    }
    ll ans = gause(A);
    printf("%lld\n", ans);
}
