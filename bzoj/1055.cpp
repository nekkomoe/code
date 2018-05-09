#include <bits/stdc++.h>

using namespace std;

const int N = 210;

int t[4], q[300], f[300][300][4];

char ch[300], a[4][20][2];

int dfs(int l, int r, int k) {
    if(l == r) return ch[l] == "WING"[k];
    int &rt = f[l][r][k];
    if(~ rt) return rt;
    for(int i = 1 ; i <= t[k] ; ++ i) {
        for(int j = l ; j <= r - 1 ; ++ j) {
            if(dfs(l, j, q[a[k][i][0]]) && dfs(j + 1, r, q[a[k][i][1]])) {
                return rt = 1;
            }
        }
    }
    return rt = 0;
}

int main() {
    memset(f, -1, sizeof f);
    q['G'] = (q['N'] = (q['I'] = (q['W'] = 0) + 1) + 1) + 1;
    for(int i = 0 ; i < 4 ; ++ i) scanf("%d", &t[i]);
    for(int i = 0 ; i < 4 ; ++ i) {
        for(int j = 1 ; j <= t[i] ; ++ j) {
            scanf("%s", a[i][j]);
        }
    }
    int n = strlen(ch + scanf("%s", ch + 1)), fl = 0;
    for(int i = 0 ; i < 4 ; ++ i) if(dfs(1, n, i)) fl = 1, putchar("WING"[i]);
    if(!fl) puts("The name is wrong!");
}
