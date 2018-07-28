#include "bits/stdc++.h"
using namespace std;
const int N = 1010;
int n, m, a[N], b[N];
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &b[i]);

    double tmp = 1;

    for(int i = 1 ; i <= n ; ++ i) {
        if(a[i] <= 1 || b[i] <= 1) return puts("-1"), 0;
        tmp = tmp * ((double) a[i] - 1) / a[i];
        tmp = tmp * ((double) b[i] - 1) / b[i];
    }
    printf("%lf\n", m / tmp - m);
}
