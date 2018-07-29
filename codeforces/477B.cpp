#include "bits/stdc++.h"
using namespace std;
const int N = 1e4 + 10;
int ans[N][4], n, k;
int main() {
    scanf("%d%d", &n, &k);
    int tmp = -1;
    for(int i = 1 ; i <= n ; ++ i) {
        ans[i][0] = (tmp += 2);
        ans[i][1] = tmp + 1;
        ans[i][2] = (tmp += 2);
        ans[i][3] = (tmp += 2);
    }
    printf("%d\n", tmp * k);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d %d %d %d\n", ans[i][0] * k, ans[i][1] * k, ans[i][2] * k, ans[i][3] * k);
    }
}
