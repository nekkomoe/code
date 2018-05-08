#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, x[N], y[N], w[N];

typedef double db;

db ax, ay, d;

db dis(db x1, db y1, db x2, db y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

db calc(db a, db b) {
    db res = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        res += w[i] * dis(a, b, x[i], y[i]);
    }
    if(res < d) {
        d = res, ax = a, ay = b;
    }
    return res;
}



int main() {
    srand((unsigned long long) new char);
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        ax += x[i], ay += y[i];
    }
    ax /= n, ay /= n, d = calc(ax, ay);
    printf("%.3lf %.3lf\n", ax, ay);
}
