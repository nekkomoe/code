#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull C[110][110];

struct POLY {
    ull f[64]; // x^0 ~ x^63
    POLY() { memset(f, 0, sizeof f); }
    ull &operator [] (int x) {
        return f[x];
    }
    POLY operator * (POLY g) {
        POLY res;
        for(int i = 0 ; i < 64 ; ++ i) {
            for(int j = 0 ; i + j < 64 ; ++ j) {
                res[i + j] += f[i] * g[j];
            }
        }
        return res;
    }
    POLY getnew(ull n) {
        POLY res;
        for(int j = 0 ; j < 64 ; ++ j) {
            ull fac = 1;
            for(int i = j ; i < 64 ; ++ i) {
                res[j] += C[i][j] * fac * f[i];
                fac *= n;
            }
        }
        return res;
    }
};

POLY sol(ull n) {
    if(n == 0) {
        POLY res;
        res[0] = 1;
        return res;
    } else if(n & 1) {
        POLY lef = sol(n - 1);
        POLY rig;
        rig[0] = 2 * n - 1, rig[1] = 2;
        return lef * rig;
    } else {
        POLY lef = sol(n / 2);
        POLY rig = lef.getnew(n / 2);
        return lef * rig;
    }
}

void runprog() {
    ull n;
    cin >> n;
    POLY res = sol(n);
    cout << res[0] << endl;
}

int main() {
    C[0][0] = 1;
    for(int i = 1 ; i <= 100 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j <= 100 ; ++ j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    ios :: sync_with_stdio(0);
    int t; cin >> t;
    while(t --) {
        runprog();
    }
}
