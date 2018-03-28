//dp

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

char str[1010];

int T, n, f[1010], loop[1010][1010];

int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%s", str + 1);
        n = strlen(str + 1);
        memset(loop, 0, sizeof(loop));
        memset(f, 0x3f, sizeof(f));
        for(int i = 1 ; i <= n ; i ++) {
            int l = i, r = i;
            while(1 <= l && r <= n && str[l] == str[r]) {
                loop[l][r] = 1;
                l --, r ++;
            }
            l = i, r = i + 1;
            while(1 <= l && r <= n && str[l] == str[r]) {
                loop[l][r] = 1;
                l --, r ++;
            }
        }
        f[0] = 0;
        for(int i = 1 ; i <= n ; i ++) {
            for(int j = 0 ; j < i ; j ++) {
                if(loop[j + 1][i]) {
                    f[i] = min(f[i], f[j] + 1);
                }
            }
        }
        printf("%d\n", f[n]);
    }
}
