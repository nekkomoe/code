#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
void upd(ll &x, ll y) {
    x = (x + y) % mod;
}
struct Mat {
    ll a[3][3];
    Mat() {
        memset(a, 0, sizeof a);
    }
    ll *operator [] (int x) {
        return a[x];
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 3 ; ++ i) {
            for(int j = 0 ; j < 3 ; ++ j) {
                for(int k = 0 ; k < 3 ; ++ k) {
                    upd(c[i][j], a[i][k] * b[k][j] % mod);
                }
            }
        }
        return c;
    }
};
Mat pw(Mat a, ll b) {
    Mat r;
    for(int i = 0 ; i < 3 ; ++ i) {
        r[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}

Mat base, coef_non, coef_has;

int main() {

    base[0][2] = 1;
    coef_has[0][0] = coef_has[1][0] = coef_has[2][0] = coef_has[1][1] = coef_has[2][2] = 1;
    coef_has[2][1] = 2;

    coef_non[0][0] = coef_non[1][0] = coef_non[2][0] = coef_non[1][1] = coef_non[0][2] = coef_non[1][2] = 1;
    coef_non[2][1] = coef_non[2][2] = 2;
    

    int n, m, lst = 0; scanf("%d%d", &n, &m);
    for(int i = 1, x ; i <= m ; ++ i) {
        scanf("%d", &x);
        base = base * pw(coef_non, x - lst - 1) * coef_has;
        lst = x;
    }
    if(lst < n) {
        int x = n;
        base = base * pw(coef_non, x - lst - 1) * coef_has;
    }

    // for(int i = 0 ; i < 3 ; ++ i) {
    //     for(int j = 0 ; j < 3 ; ++ j) {
    //         printf("%lld ", (base[i][j] % mod + mod) % mod);
    //     }
    //     puts("");
    // }
    printf("%lld\n", (base[0][0] % mod + mod) % mod);
}
