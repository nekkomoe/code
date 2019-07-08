#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n, m;

double ans[N];
int x[N], y[N], z[N];

int main() {
    srand(19260817);
    scanf("%d%d", &n, &m);

    for(int i = m + 1 ; i <= n ; ++ i) {
        scanf("%d%d", &x[i], &y[i]);
    }

    int CNT = int(1e8) / n;

    for(int i = 1 ; i <= CNT ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            z[j] = rand();
        }
        for(int j = m + 1 ; j <= n ; ++ j) {
            z[j] = min(z[x[j]], z[y[j]]);
            ans[j] += z[j] / CNT;
        }
    }

    for(int i = m + 1 ; i <= n ; ++ i) {
        printf("%.0lf\n", RAND_MAX / ans[i] - 1);
    }
}
