//数学概率

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const double eps = 1e-6;

int n;
double a, b, s, rect, ans;

int main() {
    scanf("%d", &n);
    while(n --) {
        scanf("%lf%lf%lf", &a, &b, &s);
        rect = a * b;
        if(fabs(s) < eps) ans = 100;
        else if(s >= rect) ans = 0;
        else ans = (rect - s - s * log(rect / s)) * 100 / rect;
        printf("%.6lf%%\n", ans);
    }
}
