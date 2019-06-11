#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 310;

int n, r;
double p[N], d[N];
double f[N][N];

double pw(double a, int b) {
    double r = 1;
    for( ; b ; b >>= 1, a *= a) {
        if(b & 1) {
            r *= a;
        }
    }
    return r;
}

void runprog() {
    scanf("%d%d", &n, &r);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lf%lf", &p[i], &d[i]);
    }

    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 0 ; j <= min(i, r) ; ++ j) {
            f[i][j] += f[i - 1][j - 1] * (1 - pw(1 - p[i], r - j + 1));
            f[i][j] += f[i - 1][j] * pw(1 - p[i], r - j);
        }
    }

    double ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        double s = 0;
        for(int j = 0 ; j <= min(r, i - 1) ; ++ j) {
            s += f[i - 1][j] * (1 - pw(1 - p[i], r - j));
        }
        ans += s * d[i];
    }
    printf("%.10lf\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
