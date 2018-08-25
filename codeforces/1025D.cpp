#include "bits/stdc++.h"
using namespace std;
const int N = 710;
int L[N][N], R[N][N], f[N][N], vis[N][N], n, a[N];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), L[i][i] = R[i][i] = 1, f[i][i] = 1;
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= i ; ++ j)
                vis[j][i] = vis[i][j] = gcd(a[i], a[j]) != 1;
    for(int len = 1 ; len <= n ; ++ len)
        for(int i = 1 ; i + len - 1 <= n ; ++ i) {
            int j = i + len - 1;
            for(int k = i ; k <= j ; ++ k) {
                if(L[i][k] && R[k][j]) {
                    f[i][j] = 1;
                    if(vis[k][i - 1]) R[i - 1][j] = 1;
                    if(vis[k][j + 1]) L[i][j + 1] = 1;
                }
            }
        }
    puts(f[1][n] ? "Yes" : "No");
}
