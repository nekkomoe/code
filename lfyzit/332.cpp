#include "bits/stdc++.h"
using namespace std;

const int lim = 1e5, N = lim + 10, sz = 1000;

int n, m, lst[N], a[N], bel[N], L[N], R[N], f[110][N];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int id = bel[i] = (i - 1) / sz + 1;
        R[id] = i, L[id] = L[id] ? L[id] : i;
    }
    int endpos = bel[n];
    for(int blk = 1 ; blk <= endpos ; ++ blk) {
        memset(lst, 0, sizeof lst);
        for(int i = L[blk] ; i <= R[blk] ; ++ i) lst[a[i]] = a[i];
        for(int i = 1 ; i <= lim ; ++ i) lst[i] = max(lst[i], lst[i - 1]);
        for(int i = 1 ; i <= lim ; ++ i) {
            for(int j = 0 ; j <= lim ; j += i) {
                f[blk][i] = max(f[blk][i], lst[min(j + i - 1, lim)] - j);
            }
        }
    }
    while(m --) {
        int l, r, k, ans = 0; scanf("%d%d%d", &l, &r, &k);
        if(bel[l] == bel[r]) {
            for(int i = l ; i <= r ; ++ i) {
                ans = max(ans, a[i] % k);
            }
        } else {
            for(int i = R[bel[l]] ; i >= l ; -- i) {
                ans = max(ans, a[i] % k);
            }
            for(int i = L[bel[r]] ; i <= r ; ++ i) {
                ans = max(ans, a[i] % k);
            }
            for(int i = bel[l] + 1 ; i <= bel[r] - 1 ; ++ i) {
                ans = max(ans, f[i][k]);
            }
        }
        printf("%d\n", ans);
    }
}
