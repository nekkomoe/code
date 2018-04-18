#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 100010;
 
int n, m, l, r, f[N][30], LOG[N];
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &f[i][0]), f[i - 1][0] = abs(f[i - 1][0] - f[i][0]);
    for(int i = 2 ; i <= n ; ++ i) LOG[i] = LOG[i >> 1] + 1;
    for(int j = 1 ; j <= 25 ; ++ j)
        for(int i = 1 ; (i + (1 << j) - 1) <= n ; ++ i)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    while(m --) {
        scanf("%d%d", &l, &r);
        if(l == r) puts("YES");
        else {
            -- r;
            int t = LOG[r - l + 1];
            if(max(f[l][t], f[r - (1 << t) + 1][t]) <= 1) puts("YES");
            else puts("NO");
        }
    }
}
