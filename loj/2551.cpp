#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e5 + 10, lim = 1e6, T = 2e7 + 10;
int n, m, rt[N];
ll sum[T];
int sz[T], lc[T], rc[T], tot;
void modify(int lst, int &cur, int l, int r, int pos) {
    lc[cur] = lc[lst], rc[cur] = rc[lst];
    sz[cur] = sz[lst] + 1, sum[cur] = sum[lst] + pos;
    int mid = (l + r) >> 1;
    if(l == r) {
        return ;
    } else if(pos <= mid) {
        modify(lc[lst], lc[cur] = ++ tot, l, mid, pos);
    } else {
        modify(rc[lst], rc[cur] = ++ tot, mid + 1, r, pos);
    }
}
ll ask(int L, int R, int l, int r, int use, int k) {
    int mid = (l + r) >> 1;
    int SZ = sz[R] - sz[L];
    ll SUM = sum[R] - sum[L];
    if(!SZ) {
        return 0;
    } else if(k + use <= l) {
        return SUM - (2ll * (k + use) + SZ - 1) * SZ / 2;
    } else if(r <= k + use + SZ - 1) {
        return (2ll * (k + use) + SZ - 1) * SZ / 2 - SUM;
    } else {
        return
            ask(lc[L], lc[R], l, mid, use, k)
          + ask(rc[L], rc[R], mid + 1, r, use + sz[lc[R]] - sz[lc[L]], k);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        modify(rt[i - 1], rt[i] = ++ tot, 1, lim, x);
    }
    for(int i = 1, l, r, k ; i <= m ; ++ i) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%lld\n", ask(rt[l - 1], rt[r], 1, lim, 0, k));
    }
}
