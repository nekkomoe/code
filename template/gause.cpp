#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

const int N = 110;

typedef long double ld;

const ld eps = 1e-9;

ld a[110][110];

int n;

void output() {
    puts("");
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            printf("%.2Lf ", a[i][j]);
        }
        printf(" | %.2Lf\n", a[i][n + 1]);
    }
    puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= n + 1 ; ++ j) {
            scanf("%Lf", &a[i][j]);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int id = i;
        for(int j = i ; j <= n ; ++ j) {
            if(fabs(a[j][i]) > fabs(a[id][i])) {
                id = j;
            }
        }
        if(id != i) {
            for(int j = 1 ; j <= n + 1 ; ++ j) {
                swap(a[i][j], a[id][j]);
            }
        }
        if(fabs(a[i][i]) < eps) {
            puts("No Solution");
            return 0;
        }
        for(int j = i + 1 ; j <= n ; ++ j) {
            double div = a[j][i] / a[i][i];
            for(int k = i ; k <= n + 1 ; ++ k) {
                a[j][k] -= a[i][k] * div;
            }
        }
    }
    a[n][n + 1] /= a[n][n];
    for(int i = n - 1 ; i >= 1 ; -- i) {
        for(int j = i + 1 ; j <= n ; ++ j) {
            a[i][n + 1] -= a[i][j] * a[j][n + 1];
        }
        if(fabs(a[i][i]) < eps && fabs(a[i][n + 1] > eps)) {
            puts("No Solution");
            return 0;
        }
        a[i][n + 1] /= a[i][i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%.2Lf\n", a[i][n + 1]);
    }
    return 0;
}
