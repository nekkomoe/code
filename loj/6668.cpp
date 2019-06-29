#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;

ui n, m, x, ans;

ui C[110][110];

ui a[1010], b[1010], c[1010], mem[1010], top;

inline void mns(ui *a, ui *b, ui *res, int n) {
    for(int i = 0 ; i < n ; ++ i) res[i] = a[i] - b[i];
}

inline void pls(ui *a, ui *b, ui *c, ui *res, int n) {
    for(int i = 0 ; i < n ; ++ i) res[i] = a[i] + b[i] + c[i];
}

inline ui *_new(int x) {
    ui *res = mem + top;
    top += x;
    return res;
}

void sol(ui *a, ui *b, ui *res, int n) {
    if(n == 1) {
        res[0] = a[0] * b[0];
        res[1] = 0;
    } else if(n > 1) {
        ui *a0b0 = _new(n);
        ui *a1b1 = _new(n); 
        ui *a0a1 = _new(n);
        ui *b1b0 = _new(n);
        ui *a0a1_b1b0 = _new(n); 

        sol(a, b, a0b0, n / 2);
        sol(a + n / 2, b + n / 2, a1b1, n / 2);
        mns(a, a + n / 2, a0a1, n / 2);
        mns(b + n / 2, b, b1b0, n / 2);
        sol(a0a1, b1b0, a0a1_b1b0, n / 2);

        for(int i = 0 ; i < n ; ++ i) {
            res[i] = a0b0[i];
            res[i + n] = a1b1[i];
        }
        pls(a0a1_b1b0, a1b1, a0b0, a0a1_b1b0, n);
        for(int i = 0 ; i < n ; ++ i) {
            res[i + n / 2] += a0a1_b1b0[i];
        }

        top -= 5 * n;
    }
}

struct POLY {
    ui f[32]; // x^0 ~ x^31
    POLY() { memset(f, 0, sizeof f); }
    inline ui &operator [] (int x) {
        return f[x];
    }
    inline POLY operator * (POLY g) {
        POLY res;
        // for(int i = 0 ; i < 32 ; ++ i) {
        //     for(int j = 0 ; i + j < 32 ; ++ j) {
        //         res[i + j] += f[i] * g[j];
        //     }
        // }
        for(int i = 0 ; i < 32 ; ++ i) {
            a[i] = f[i];
            b[i] = g[i];
        }
        for(int i = 32 ; i < 64 ; ++ i) {
            a[i] = 0;
            b[i] = 0;
        }

        sol(a, b, c, 64);
        for(int i = 0 ; i < 32 ; ++ i) {
            res[i] = c[i];
        }

        return res;
    }
    inline POLY operator * (ui n) {
        POLY res;
        for(int i = 0 ; i < 32 ; ++ i) {
            res[i] = f[i] * n;
        }
        return res;
    }
    inline POLY operator + (POLY g) {
        POLY res;
        for(int i = 0 ; i < 32 ; ++ i) {
            res[i] = f[i] + g[i];
        }
        return res;
    }
    inline POLY getnew(ui n) {
        POLY res;
        for(int j = 0 ; j < 32 ; ++ j) {
            ui fac = 1;
            for(int i = j ; i < 32 ; ++ i) {
                res[j] += C[i][j] * fac * f[i];
                fac *= n;
            }
        }
        return res;
    }
};

inline POLY f(ui n) {
    if(n == 0) {
        POLY res;
        res[0] = 1;
        return res;
    } else if(n & 1) {
        POLY lef = f(n - 1);
        POLY rig;
        rig[0] = 2 * n - 1, rig[1] = 2;
        return lef * rig;
    } else {
        POLY lef = f(n / 2);
        POLY rig = lef.getnew(n / 2);
        return lef * rig;
    }
}

inline POLY F(ui n) {
    if(n == 0) {
        POLY res;
        return res;
    } else if(n & 1) {
        POLY lef = F(n - 1);
        POLY rig = f(n);
        return lef + rig;
    } else {
        POLY lef = F(n / 2);
        POLY rig = f(n / 2) * lef.getnew(n / 2);
        return lef + rig;
    }
}

unordered_map<ui, ui> askmem;
inline ui calc(ui n) {
    if(n == 0) return 0;
    if(askmem.count(n)) return askmem[n];
    return askmem[n] = F(n)[0];
}

int main() {

    C[0][0] = 1;
    for(int i = 1 ; i <= 100 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= 100 ; ++ j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    cin >> n >> m >> x;
    ++ n, ++ m; // lcp < len
    for(ui i = 31 ; ~ i ; -- i) {
        if((n >> i) & 1) {
            for(ui j = 31 ; ~ j ; -- j) {
                if((m >> j) & 1) {
                    ui mn = min(i, j), mx = max(i, j);
                    ui sum = x ^ (x & ((1ll << mx) - 1));
                    ui N = n ^ (1ll << i), M = m ^ (1ll << j);
                    sum ^= N ^ (N & ((1ll << mx) - 1));
                    sum ^= M ^ (M & ((1ll << mx)) - 1);

                    ui tmp = calc(sum ^ ((1ll << mx) - 1));
                    if(sum >= 1) tmp -= calc(sum - 1);
                    ans += tmp * (1ll << mn);
                }
            }
        }
    }
    cout << ans << endl;
}
