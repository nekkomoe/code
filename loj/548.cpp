#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int mod = 232792561, g = 71, M = 26, N = 1e6 + 10;

int n, m, cnt[M];
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

int A[M][M], lim;

ll f[N], tmp[N], C[M][M], D[M][M];
void fwt(ll *f, int n, ll C[M][M]) {
    if(n == 1) return ;
    int len = n / m;
    for(int i = 0 ; i < m ; ++ i) fwt(f + i * len, len, C);
    for(int i = 0 ; i < n ; ++ i) tmp[i] = 0;
    for(int i = 0 ; i < m ; ++ i) {
        for(int j = 0 ; j < m ; ++ j) {
            for(int k = 0 ; k < len ; ++ k) {
                (tmp[j * len + k] += f[i * len + k] * C[i][j] % mod) %= mod;
            }
        }
    }
    for(int i = 0 ; i < n ; ++ i) f[i] = tmp[i];
}

int c[M];
ll w[30][M], a[M];
void init() {
    for(int i = 1 ; i <= 22 ; ++ i) {
        ll wn = pw(g, (mod - 1) / i), prod = 1;
        for(int j = 0 ; j < i ; ++ j) {
            w[i][j] = prod;
            prod = prod * wn % mod;
        }
    }
    for(int i = 0 ; i < m ; ++ i) {
        int j = i;
        do {
            ++ cnt[i];
            j = A[j][i];
        } while(j != i);
    }
}
int check(int n) {
    for(int i = 0 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= n ; ++ j) {
            if(A[i][j] <= n && a[i] * a[j] % mod != a[A[i][j]]) {
                return 0;
            }
        }
    }
    return 1;
}

int tot;
void dfs(int stp) {
    if(tot == m) {
        return;
    }
    if(stp == m) {
        int flag = 1;
        for(int i = 0 ; i < m ; ++ i) {
            if(a[i]) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            return;
        }
        for(int i = 0 ; i < m ; ++ i) {
            C[i][tot] = a[i];
        }
        ++ tot;
    } else {
        for(int i = 0 ; i <= cnt[stp] ; ++ i) {
            a[stp] = w[cnt[stp]][i];
            if(check(stp)) {
                dfs(stp + 1);
            }
        }
    }
}

void getinv() {
    for(int i = 0 ; i < m ; ++ i) {
        D[i][i] = 1;
    }
    for(int i = 0 ; i < m ; ++ i) {
        int cho = i;
        for(int j = i + 1 ; j < m ; ++ j) {
            if(C[j][i]) {
                cho = j;
                break;
            }
        }
        if(cho != i) {
            for(int j = 0 ; j < m ; ++ j) {
                swap(C[i][j], C[cho][j]);
                swap(D[i][j], D[cho][j]);
            }
        }
        ll inv = pw(C[i][i], mod - 2);
        for(int j = 0 ; j < m ; ++ j) {
            (C[i][j] *= inv) %= mod;
            (D[i][j] *= inv) %= mod;
        }
        for(int j = 0 ; j < m ; ++ j) {
            if(j != i && C[j][i]) {
                ll tmp = C[j][i];
                for(int k = 0 ; k < m ; ++ k) {
                    (C[j][k] -= tmp * C[i][k] % mod) %= mod;
                    (D[j][k] -= tmp * D[i][k] % mod) %= mod;
                }
            }
        }
    }
}

int main() {
    ll T;
    scanf("%d%d%lld", &n, &m, &T);
    T = (T + 1) % (mod - 1);
    for(int i = 0 ; i < m ; ++ i) {
        for(int j = 0 ; j < m ; ++ j) {
            scanf("%d", &A[i][j]);
        }
    }
    init();

    lim = pw(m, n);
    dfs(0);
    for(int i = 0 ; i < lim ; ++ i) {
        scanf("%lld", &f[i]);
    }

    fwt(f, lim, C);

    for(int i = 0 ; i < lim ; ++ i) {
        f[i] = pw(f[i], T);
    }
    getinv();
    fwt(f, lim, D);

    for(int i = 0 ; i < lim ; ++ i) {
        printf("%lld\n", (f[i] % mod + mod) % mod);
    }
}
