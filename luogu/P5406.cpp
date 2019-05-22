// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353, inv2 = (mod + 1) / 2;

inline void add(ll &x, ll y) {
    x = (x + y) % mod;
    // if(x < 0) x += mod;
}

inline void sub(ll &x, ll y) {
    x = (x - y) % mod;
    // if(x < 0) x += mod;
}

inline void mul(ll &x, ll y) {
    x = x * y % mod;
    // if(x < 0) x += mod;
}

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
ll inv(ll a) {
    return pw(a, mod - 2);
}

int n, m, w; char ops[110];
ll nek[1 << 13], mxv;

ll f[110][110], a[110][110][1 << 13];

template<int ty> void fwt(ll *f) {
    for(int i = 0 ; i < w ; ++ i) {
        int bit = 1 << i;
        if(ops[i] == '|') {
            for(int j = 0 ; j < mxv ; ++ j) {
                if(j & bit) {
                    (ty ? sub : add)(f[j], f[j ^ bit]);
                }
            }
        } else if(ops[i] == '&') {
            for(int j = 0 ; j < mxv ; ++ j) {
                if(j & bit) {
                    (ty ? sub : add)(f[j ^ bit], f[j]);
                }
            }
        } else {
            for(int j = 0 ; j < mxv ; ++ j) {
                if((j & bit) == 0) {
                    ll u = f[j], v = f[j ^ bit];
                    f[j] = (u + v) % mod;
                    f[j ^ bit] = (u - v) % mod;
                }
            }
        }
    }
    if(ty) {
        ll x = 1;
        for(int i = 0 ; i < w ; ++ i) {
            if(ops[i] == '^') {
                mul(x, inv2);
            }
        }
        if(x != 1) {
            for(int i = 0 ; i < mxv ; ++ i) {
                mul(f[i], x);
            }
        }
    }
}

ll calc() {
    ll res = 1;
    for(int i = 1 ; i < n ; ++ i) {
        if(f[i][i] == 0) {
            for(int j = i + 1 ; j < n ; ++ j) {
                if(f[j][i]) {
                    for(int k = 1 ; k < n ; ++ k) {
                        swap(f[i][k], f[j][k]);
                    }
                    break;
                }
            }
            mul(res, -1);
        }
        ll iv = inv(f[i][i]);
        mul(res, f[i][i]);
        for(int j = i + 1 ; j < n ; ++ j) {
            if(f[j][i]) {
                ll prod = iv * f[j][i] % mod;
                for(int k = i ; k < n ; ++ k) {
                    sub(f[j][k], prod * f[i][k] % mod);
                }
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d%s", &n, &m, ops);
    w = strlen(ops);
    mxv = 1 << w;
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        if(u != v) {
            -- u, -- v;
            sub(a[u][v][c], 1);
            sub(a[v][u][c], 1);
            add(a[u][u][c], 1);
            add(a[v][v][c], 1);
        }
    }
    for(int i = 0 ; i < n ; ++ i) {
        for(int j = 0 ; j <= i ; ++ j) {
            fwt<0>(a[i][j]);
            if(i > j) {
                memcpy(a[j][i], a[i][j], sizeof a[i][j]);
            }
        }
    }
    for(int i = 0 ; i < mxv ; ++ i) {
        for(int u = 0 ; u < n ; ++ u) {
            for(int v = 0 ; v < n ; ++ v) {
                f[u][v] = a[u][v][i];
            }
        }
        nek[i] = calc();
    }
    fwt<1>(nek);
    for(int i = mxv ; ~ i ; -- i) {
        if(nek[i]) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("-1");
}
