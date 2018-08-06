#include "bits/stdc++.h"
using namespace std;
const int N = 20;
int s[N], n, k, p[N];
long long f[1 << N][N], ans;
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &s[i]);
        f[p[i] = (1 << (i - 1))][i] = 1;
    }
    for(int S = 0 ; S < (1 << n) ; ++ S) {
        for(int i = 1 ; i <= n ; ++ i) {
            if(S & p[i]) {
                for(int j = 1 ; j <= n ; ++ j) {
                    if(abs(s[j] - s[i]) > k && !(S & p[j])) {
                        f[S | p[j]][j] += f[S][i];
                    }
                }
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        ans += f[(1 << n) - 1][i];
    }
    printf("%lld\n", ans);
}
