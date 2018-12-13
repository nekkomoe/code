#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;

ll a[N];

int lc[N * 32], rc[N * 32], tot, root[N]; ll sum[N * 32];

void poi(int now, int last, int l, int r, int x) {
    int mid = ((ll) l + r) >> 1;
    sum[now] = sum[last] + x;
    lc[now] = lc[last], rc[now] = rc[last];
    if(l == r) {
        return ;
    } else if(x <= mid) {
        poi(lc[now] = ++ tot, lc[last], l, mid, x);
    } else {
        poi(rc[now] = ++ tot, rc[last], mid + 1, r, x);
    }
}

ll ask(int L, int R, int l, int r, int x) {
    int mid = ((ll) l + r) >> 1;
    if(l == r) {
        return sum[R] - sum[L];
    } else if(x <= mid) {
        return ask(lc[L], lc[R], l, mid, x);
    } else {
        return sum[lc[R]] - sum[lc[L]] + ask(rc[L], rc[R], mid + 1, r, x);
    }
}

ll ask(int l, int r) {
    ll ans = 1;
    while(1) {
        ll cnt = ask(root[l - 1], root[r], 1, 1e9, ans);
        if(cnt < ans) break;
        else ans = cnt + 1;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        poi(root[i] = ++ tot, root[i - 1], 1, 1e9, a[i]);
    }
    scanf("%d", &m);
    for(int i = 1, l, r ; i <= m ; ++ i) {
        scanf("%d%d", &l, &r);
        printf("%lld\n", ask(l, r));
    }
} 

