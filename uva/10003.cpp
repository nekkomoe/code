//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int L, n, pos[60], f[60][60];

int main() {
    while(scanf("%d", &L) == 1 && L) {
        scanf("%d", &n);
        for(int i = 1 ; i <= n ; i ++) {
            scanf("%d", &pos[i]);
        }
        pos[0] = 0;
        pos[n + 1] = L;
        memset(f, 0x3f, sizeof(f));
        for(int len = 1 ; len <= n + 1 ; len ++) {
            for(int i = 0 ; i <= n + 1 ; i ++) {
                int j = i + len;
                if(j > n + 1) break;;
                for(int k = i + 1 ; k < j ; k ++) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k][j] + pos[j] - pos[i]);
                }
                if(f[i][j] == 0x3f3f3f3f) {
                    f[i][j] = 0;
                }
            }
        }
        printf("The minimum cutting is %d.\n", f[0][n + 1]);
    }
}
