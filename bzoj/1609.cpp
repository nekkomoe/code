//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 30010;

int f[N][5], n, d[N], ans = 0x3f3f3f3f;

void work() {
    memset(f, 0x3f, sizeof(f));
    f[0][1] = f[0][2] = f[0][3] = 0;
    for(int i = 1 ; i <= n ; i ++) {
        for(int j = 1 ; j <= 3 ; j ++) {
            for(int k = 1 ; k <= j ; k ++) {
                if(d[i] == j) {
                    f[i][j] = min(f[i][j], f[i - 1][k]);
                } else {
                    f[i][j] = min(f[i][j], f[i - 1][k] + 1);
                }
            }
        }
    }
    ans = min(ans, min(f[n][1], min(f[n][2], f[n][3])));
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%d", &d[i]);
    }
    work();
    reverse(d + 1, d + 1 + n);
    work();
    printf("%d\n", ans);
}
