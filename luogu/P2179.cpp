#include "bits/stdc++.h"
using namespace std;

const int N = 1e4 + 10;

int n; double E, a[N], s[N], v[N], x[N];

double binX(double lambda, int pos) {
    double l = v[pos], r = 1e10;
    for(int i = 1 ; i <= 100 ; ++ i) {
        double mid = (l + r) / 2;
        if(s[pos] / (2 * a[pos] * mid * mid * (mid - v[pos])) < lambda) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

void getX(double lambda) {
    for(int i = 1 ; i <= n ; ++ i) {
        x[i] = binX(lambda, i);
    }
}

double getF(double lambda) {
    getX(lambda);
    double res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        res += s[i] / x[i];
    }
    return res;
}

double getG(double lambda) {
    getX(lambda);
    double res = -E;
    for(int i = 1 ; i <= n ; ++ i) {
        res += a[i] * (x[i] - v[i]) * (x[i] - v[i]);
    }
    return res;
}

int main() {
    scanf("%d%lf", &n, &E);
    for(int i = 1 ; i <= n ; ++ i) {
        double k;
        scanf("%lf%lf%lf", &s[i], &k, &v[i]);
        a[i] = s[i] * k;
    }
    double l = -1e10, r = 1e10;
    for(int i = 1 ; i <= 100 ; ++ i) {
        double mid = (l + r) / 2;
        if(getG(mid) < 0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.6lf\n", getF(l));
}
