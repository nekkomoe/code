#include "bits/stdc++.h"
using namespace std;
const int N = 500;
int n, a[N], lk[N][N];
char mp[N][N];
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) scanf("%s", mp[i] + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        lk[i][i] = 1;
        for(int j = 1 ; j <= n ; ++ j)
            lk[i][j] |= mp[i][j] == '1';
    }
    for(int k = 1 ; k <= n ; ++ k)
        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 1 ; j <= n ; ++ j)
                lk[i][j] |= lk[i][k] && lk[k][j];
    for(int i = 1 ; i <= n ; ++ i) {
        int ch = i;
        for(int j = i + 1 ; j <= n ; ++ j) {
            if(lk[i][j] && a[ch] > a[j]) {
                ch = j;
            }
        }
        swap(a[i], a[ch]);
        printf("%d ", a[i]);
    }
}
