#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 110;
int n, f[N][N];
char str[N];
bool check(int l, int r, int a, int b) {
    int len1 = r - l + 1, len2 = b - a + 1;
    if(len1 <= len2 && len2 % len1 == 0) {
        for(int i = a, j = l ; i <= b ; ++ i) {
            if(str[i] != str[j]) {
                return 0;
            }
            if(j + 1 <= r) ++ j; else j = l;
        }
        return 1;
    }
    return 0;
}
int get(int x) { int r = 0; while(x) x /= 10, ++ r; return r; }
int main() {
    scanf("%s", str + 1), n = strlen(str + 1);
    memset(f, 0x3f, sizeof f);
    for(int i = 1 ; i <= n ; ++ i) f[i][i] = 1;
    for(int len = 2 ; len <= n ; ++ len) {
        for(int i = 1 ; i + len - 1 <= n ; ++ i) {
            int j = i + len - 1;
            for(int k = i ; k < j ; ++ k) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                if(check(i, k, k + 1, j)) f[i][j] = min(f[i][j], f[i][k] + 2 + get((j - k) / (k - i + 1) + 1));
            }
        }
    }
    printf("%d\n", f[1][n]);
}
