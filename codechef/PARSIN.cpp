#include <bits/stdc++.h>
using namespace std;
#define double long double
int n, m, lim;
double X;

struct Mat {
    double a[110][110];
    double* operator [] (int x) {
        return a[x];
    }
    Mat() {
        memset(a, 0, sizeof a);
    }
    Mat operator * (Mat b) {
        Mat c;
        for(int i = 1 ; i <= lim ; ++ i) {
            for(int j = 1 ; j <= lim ; ++ j) {
                for(int k = 1 ; k <= lim ; ++ k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }
    void output() {
        for(int i = 1 ; i <= lim ; ++ i) {
            for(int j = 1 ; j <= lim ; ++ j) {
                printf("%.2Lf ", a[i][j]);
            }
            puts("");
        }
    }
};
Mat pw(Mat a, int b) {
    Mat r;
    for(int i = 1 ; i <= lim ; ++ i) {
        r[i][i] = 1;
    }
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}

int main() {
    int t; cin >> t;
    while(t --) {
        cin >> m >> n >> X;
        lim = 2 * m;
        Mat base, coef;
        for(int i = 1 ; i <= m ; ++ i) {
            if(i == 1) {
                base[1][i] = sin(X);
                base[1][m + i] = cos(X);
            } else {
                base[1][i] = 0;
                base[1][m + i] = 0;
            }

            coef[i - 1][i] = coef[m + i][i] = sin(X);
            coef[i][i] = cos(X);
            
            coef[i - 1][m + i] = coef[m + i][m + i] = cos(X);
            coef[i][m + i] = -sin(X);
        }

        base = base * pw(coef, n - 1);
        cout << fixed << setprecision(12) << base[1][m] << endl;
    }
}
