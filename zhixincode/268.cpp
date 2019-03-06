#include "bits/stdc++.h"
using namespace std;
const int N = 510;
int n, f[N], s[N];
double x[N][2], y[N][2], z[N][2];
double y_tmp[N][2], z_tmp[N][2];

double sqr(double x) { return x * x; }

double sol() {

    int loop = 50000;
    double alpha = 1e-3;

    while(loop --) {
        for(int i = 1 ; i <= n ; ++ i) {
            y_tmp[f[i]][0] -= alpha * (2.0 * y[f[i]][0] - x[i][0] - z[s[i]][0]);
            y_tmp[f[i]][1] -= alpha * (2.0 * y[f[i]][1] - x[i][1] - z[s[i]][1]);
            z_tmp[s[i]][0] -= alpha * (-y[f[i]][0] + z[s[i]][0]);
            z_tmp[s[i]][1] -= alpha * (-y[f[i]][1] + z[s[i]][1]);
        }
        memcpy(y, y_tmp, sizeof y);
        memcpy(z, z_tmp, sizeof z);
    }

    double res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        res += sqr(x[i][0] - y[f[i]][0]) + sqr(x[i][1] - y[f[i]][1]);
        res += sqr(y[f[i]][0] - z[s[i]][0]) + sqr(y[f[i]][1] - z[s[i]][1]);
    }

    return res;
}

int main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++ i) cin >> x[i][0] >> x[i][1];
    for(int i = 1 ; i <= n ; ++ i) cin >> f[i];
    for(int i = 1 ; i <= n ; ++ i) cin >> s[i];
    cout << fixed << setprecision(20) << sol() << endl;
}
