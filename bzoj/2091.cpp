#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, a[N], f[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] = max(f[i - 1], a[i] - f[i - 1]);
    }
    printf("%d\n", f[n]);
}
