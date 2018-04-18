#include <bits/stdc++.h>

using namespace std;

const int N = 50000 + 10;

int n, m, mx[N][30], mn[N][30];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &mn[i][0]), mx[i][0] = mn[i][0];
    for(int j = 1 ; j <= 25 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i) {
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
    for(int i = 1, l, r ; i <= m ; ++ i) {
        scanf("%d%d", &l, &r);
        int mn = :: mn[l][0], mx = :: mx[l][0];
        for(int j = 25 ; ~ j ; -- j) {
            if(l + (1 << j) - 1 <= r) {
                mx = max(mx, :: mx[l][j]);
                mn = min(mn, :: mn[l][j]);
                l += 1 << j;
            }
        }
        printf("%d\n", mx - mn);
    }
}
