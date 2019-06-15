// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;

int s, n, m;

void chkmin(int &a, int b) {
    a = min(a, b);
}

int f[20010];

int sta[110];

int a[110][110];

int main() {
    scanf("%d%d%d", &s, &n, &m);
    for(int i = 1 ; i <= s ; ++ i) {
        for(int j = 1 ; j <= n ; ++ j) {
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0;
    f[0] = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= s ; ++ j) {
            sta[j] = a[j][i];
        }
        sort(sta + 1, sta + 1 + s);
        for(int j = m ; j >= 0 ; -- j) {
            for(int k = 1 ; k <= s ; ++ k) {
                if(j - sta[k] * 2 - 1 >= 0) {
                    f[j] = max(f[j], f[j - sta[k] * 2 - 1] + i * k);
                }
            }
        }
    }
    printf("%d\n", f[m]);
}
