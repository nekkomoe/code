#include "bits/stdc++.h"
using namespace std;

const int N = 2e5 + 10;

int n, a[N], f[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    f[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        int j = 0;
        if(a[i - 1] * 2 >= a[i]) j = i - 1;
        f[i] = f[j] + 1;
        // printf("f[%d] = f[%d] + 1\n", i, j);
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) ans = max(ans, f[i]);
    printf("%d\n", ans);
}
