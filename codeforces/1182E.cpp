#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 1e5 + 10;

ll pw(ll a, ll b) {
    // b %= mod - 1;
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

struct Mat {
    ll a[20][20];
    Mat() {
        memset(a, 0, sizeof a);
    }
    ll *operator [] (int x) {
        return a[x];
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 1 ; i <= 9 ; ++ i) {
            for(int j = 1 ; j <= 9 ; ++ j) {
                for(int k = 1 ; k <= 9 ; ++ k) {
                    c[i][j] = (c[i][j] + a[i][k] * b[k][j] % (mod - 1)) % (mod - 1);
                }
            }
        }
        return c;
    }
    void output() {
        for(int i = 1 ; i <= 9 ; ++ i) {
            for(int j = 1 ; j <= 9 ; ++ j) {
                printf("%lld ", a[i][j]);
            }
            puts("");
        }
    }
} coef, base;

Mat pw(Mat a, ll b) {
    // b %= mod - 1;
    Mat r;
    for(int i = 1 ; i <= 9 ; ++ i) {
        r[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}

ll n, c, f1, f2, f3;
ll cnt_c, cnt_1, cnt_2, cnt_3;

int main() {
    cin >> n >> f1 >> f2 >> f3 >> c;

    coef = Mat(), base = Mat();
    base[1][1] = base[1][5] = base[1][9] = 1;
    for(int i = 4 ; i <= 9 ; ++ i) coef[i][i - 3] = 1;
    coef[1][7] = coef[4][7] = coef[7][7] = 1;
    coef[2][8] = coef[5][8] = coef[8][8] = 1;
    coef[3][9] = coef[6][9] = coef[9][9] = 1;

    // base.output(), puts("");
    // coef.output(), puts("");

    base = base * pw(coef, n - 1);
    cnt_1 = base[1][1], cnt_2 = base[1][2], cnt_3 = base[1][3];

    coef = Mat(), base = Mat();
    base[1][4] = 8, base[1][5] = 1;
    coef[2][1] = coef[3][2] = 1;
    coef[1][3] = coef[2][3] = coef[3][3] = coef[4][3] = 1, coef[5][3] = -6;
    coef[4][4] = 1, coef[5][4] = 2;
    coef[5][5] = 1;

    base = base * pw(coef, n - 1);
    cnt_c = base[1][1];    

    // printf("cnt_1 = %lld\n", cnt_1);
    // printf("cnt_2 = %lld\n", cnt_2);
    // printf("cnt_3 = %lld\n", cnt_3);
    // printf("cnt_c = %lld\n", cnt_c);

    ll ans = pw(c, cnt_c) * pw(f1, cnt_1) % mod * pw(f2, cnt_2) % mod * pw(f3, cnt_3) % mod;
    cout << (ans % mod + mod) % mod << endl;
}
