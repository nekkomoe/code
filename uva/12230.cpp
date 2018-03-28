//数学期望

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, D, p[20], L[20], v[20];
double ans;

int main() {
    for(int T = 1 ; scanf("%d%d", &n, &D) == 2 && (n || D) ; T ++) {
        ans = D;
        for(int i = 1 ; i <= n ; i ++) {
            scanf("%d%d%d", &p[i], &L[i], &v[i]);
            ans -= L[i];
            ans += 2.0 * L[i] / v[i];
        }
        printf("Case %d: %.3lf\n\n", T, ans);
    }
}
