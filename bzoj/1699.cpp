#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, q, a[N], mx[N][25], mn[N][25];

int query(int t, int l, int r) {
    int res = :: a[l];
    for(int i = 20 ; ~ i ; -- i) {
        if(l + (1 << i) - 1 <= r) {
            if(t) res = min(res, mn[l][i]);
            else res = max(res, mx[l][i]);
            l += 1 << i;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), mn[i][0] = mx[i][0] = a[i];
    for(int j = 1 ; j <= 20 ; ++ j)
        for(int i = 1 ; i + (1 << j) - 1 <= n ; ++ i)
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]),
            mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    for(int i = 1, l, r ; i <= q ; ++ i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", query(0, l, r) - query(1, l, r));
    }
}

