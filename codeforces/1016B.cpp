#include "bits/stdc++.h"
using namespace std;
const int N = 1e3 + 10;
char s[N], t[N];
int n, m, q;
int pos[N], f[N][N];
int main() {
    scanf("%d%d%d", &n, &m, &q);
    scanf("%s%s", s + 1, t + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        int flag = 1;
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[i + j - 1] != t[j]) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            pos[i] = 1;
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = i ; j <= n ; ++ j) {
            f[i][j] = f[i][j - 1];
            if(j - m + 1 >= i) f[i][j] += pos[j - m + 1];
        }
    }
    for(int i = 1, l, r ; i <= q ; ++ i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", f[l][r]);
    }
}
