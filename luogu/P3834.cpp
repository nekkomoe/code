#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10, T = 1e9;

int n, m;

int root[N], lc[N * 32], rc[N * 32], sum[N * 32], tot;

void poi(int now, int last, int l, int r, int x) {
    int mid = ((ll) l + r) >> 1;
    lc[now] = lc[last], rc[now] = rc[last], sum[now] = sum[last] + 1;
    if(l == r) {
        return ;
    } else if(x <= mid) {
        poi(lc[now] = ++ tot, lc[last], l, mid, x);
    } else {
        poi(rc[now] = ++ tot, rc[last], mid + 1, r, x);
    }
}

int ask(int L, int R, int l, int r, int k) {
    int mid = ((ll) l + r) >> 1;
    if(l == r) {
        return l;
    } else if(sum[lc[R]] - sum[lc[L]] >= k) {
        return ask(lc[L], lc[R], l, mid, k);
    } else {
        return ask(rc[L], rc[R], mid + 1, r, k - (sum[lc[R]] - sum[lc[L]]));
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        poi(root[i] = ++ tot, root[i - 1], 0, T * 2, x + T);
        
    }
    
    for(int i = 1 ; i <= m ; ++ i) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", ask(root[l - 1], root[r], 0, T * 2, k) - T);
    }
} 

