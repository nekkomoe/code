// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

struct FWT {
    ll mod, g;
    vector<vector<ll> > A, C, D, w;
    vector<ll> f, cnt, tmp, a;

    // 快速幂
    ll pw(ll a, ll b) {
        ll r = 1;
        for( ; b ; b >>= 1, a = a * a % mod) {
            if(b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    }

    int m; // m进制

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
        vector<vector<ll> > C_mem = C;
        for(int i = 0 ; i < m ; ++ i) {
            D[i][i] = 1;
        }
        for(int i = 0 ; i < m ; ++ i) {
            if(!C[i][i]) {
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
        C = C_mem;
    }

    FWT(int inp_m, int inp_g, int inp_mod, vector<vector<ll> > inp_A) {
        m = inp_m; // 初始化进制
        g = inp_g; // 初始化原根
        mod = inp_mod; // 初始化模数
        A = inp_A; // 初始化系数表
        w.clear(), w.resize(m + 1);
        for(int i = 1 ; i <= m ; ++ i) {
            w[i].clear(), w[i].resize(m + 1);
            ll wn = pw(g, (mod - 1) / i), prod = 1;
            for(int j = 0 ; j < i ; ++ j) {
                w[i][j] = prod;
                prod = prod * wn % mod;
            }
        }
        cnt.clear(), cnt.resize(m);
        for(int i = 0 ; i < m ; ++ i) {
            int j = i;
            do {
                ++ cnt[i];
                j = A[j][i];
            } while(j != i);
        }
        C.clear(), C.resize(m);
        D.clear(), D.resize(m);
        for(int i = 0 ; i < m ; ++ i) {
            C[i].clear(), C[i].resize(m);
            D[i].clear(), D[i].resize(m);
        }
        a.clear(), a.resize(m);
        tot = 0;
        dfs(0);
        getinv();
    }

    void __dft(int ops, int n) {
        if(n == 1) return ;
        int len = n / m;
        for(int i = 0 ; i < m ; ++ i) __dft(ops + i * len, len);
        tmp.clear(), tmp.resize(n);
        for(int i = 0 ; i < m ; ++ i) {
            for(int j = 0 ; j < m ; ++ j) {
                for(int k = 0 ; k < len ; ++ k) {
                    (tmp[j * len + k] += f[ops + i * len + k] * C[i][j] % mod) %= mod;
                }
            }
        }
        for(int i = 0 ; i < n ; ++ i) f[ops + i] = tmp[i];
    }

    vector<ll> dft(vector<ll> inp) {
        f = inp;
        __dft(0, f.size());
        for(int i = 0 ; i < f.size() ; ++ i) {
            if(f[i] < 0) {
                f[i] += mod;
            }
        }
        return f;
    }

    void __idft(int ops, int n) {
        if(n == 1) return ;
        int len = n / m;
        for(int i = 0 ; i < m ; ++ i) __idft(ops + i * len, len);
        tmp.clear(), tmp.resize(n);
        for(int i = 0 ; i < m ; ++ i) {
            for(int j = 0 ; j < m ; ++ j) {
                for(int k = 0 ; k < len ; ++ k) {
                    (tmp[j * len + k] += f[ops + i * len + k] * D[i][j] % mod) %= mod;
                }
            }
        }
        for(int i = 0 ; i < n ; ++ i) f[ops + i] = tmp[i];
    }

    vector<ll> idft(vector<ll> inp) {
        f = inp;
        __idft(0, f.size());
        for(int i = 0 ; i < f.size() ; ++ i) {
            if(f[i] < 0) {
                f[i] += mod;
            }
        }
        return f;
    }

    vector<ll> getmul(vector<ll> a, vector<ll> b) {
        a = dft(a), b = dft(b);
        for(int i = 0 ; i < a.size() ; ++ i) {
            a[i] = a[i] * b[i] % mod;
        }
        return idft(a);
    }

    vector<ll> getpow(vector<ll> a, ll k) {
        a = dft(a);
        for(int i = 0 ; i < a.size() ; ++ i) {
            a[i] = pw(a[i], k);
        }
        a = idft(a);
        return a;
    }
};

const int mod = 998244353, g = 3;

vector<ll> a, b;

vector<vector<ll> > get_and() {
    vector<vector<ll> > A;
    A.resize(2), A[0].resize(2), A[1].resize(2);
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            A[i][j] = i & j;
        }
    }
    return A;
}

vector<vector<ll> > get_or() {
    vector<vector<ll> > A;
    A.resize(2), A[0].resize(2), A[1].resize(2);
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            A[i][j] = i | j;
        }
    }
    return A;
}

vector<vector<ll> > get_xor() {
    vector<vector<ll> > A;
    A.resize(2), A[0].resize(2), A[1].resize(2);
    for(int i = 0 ; i < 2 ; ++ i) {
        for(int j = 0 ; j < 2 ; ++ j) {
            A[i][j] = i ^ j;
        }
    }
    return A;
}

void sol(vector<vector<ll> > A) {
    FWT fwt(2, g, mod, A);
    vector<ll> res = fwt.getmul(a, b);
    for(int i = 0 ; i < res.size() ; ++ i) {
        printf("%lld ", res[i]);
    }
    puts("");
}

int main() {
    int n; scanf("%d", &n); n = 1 << n;
    a.resize(n), b.resize(n);
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld", &a[i]);
    }
    for(int i = 0 ; i < n ; ++ i) {
        scanf("%lld", &b[i]);
    }
    sol(get_or());
    sol(get_and());
    sol(get_xor());
}
