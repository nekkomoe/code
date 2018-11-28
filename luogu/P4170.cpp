#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int N = 60;
 
int n;
 
char str[N];
 
int f[N][N];
 
int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    memset(f, 0x3f, sizeof f);
    for(int i = 1 ; i <= n ; ++ i) f[i][i] = 1;
    for(int len = 2 ; len <= n ; ++ len) {
        for(int i = 1, j ; (j = i + len - 1) <= n ; ++ i) {
            if(str[i] == str[j]) {
                if(len == 2)
                    f[i][j] = 1;
                else
                    f[i][j] = min(min(f[i + 1][j], f[i][j - 1]), min(f[i][j], 1 + f[i + 1][j - 1]));
            }
            for(int k = i ; k < j ; ++ k) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }
    printf("%d\n", f[1][n]);
}
