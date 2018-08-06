#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

int sum[N * 30] ,lc[N * 30], rc[N * 30], rt[N], cnt;

void modify(int now, int last, int l, int r, int pos) {
    while(l < r) {
        int mid = (l + r) >> 1;
        sum[now] = sum[last] + 1;
        lc[now] = lc[last], rc[now] = rc[last];
        if(pos <= mid) {
            r = mid;
            lc[now] = ++ cnt, now = lc[now];
            last = lc[last];
        } else {
            l = mid + 1;
            rc[now] = ++ cnt, now = rc[now];
            last = rc[last];
        }
    }
    sum[now] = sum[last] + 1;
}

int query(int ln, int rn, int l, int r, int len) {
    while(l < r) {
        int mid = (l + r) >> 1;
        int ss = sum[rn[lc]] - sum[ln[lc]];
        if(ss > len) {
            r = mid;
            ln = ln[lc], rn = rn[lc];
        } else {
            l = mid + 1;
            ln = ln[rc], rn = rn[rc];
        }
    }
    return sum[rn] - sum[ln] > len ? l : 0;
}

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, x ; i <= n ; ++ i) scanf("%d", &x), modify(rt[i] = ++ cnt, rt[i - 1], 1, n, x);
    for(int i = 1, l, r ; i <= m ; ++ i) scanf("%d%d", &l, &r), printf("%d\n", query(rt[l - 1], rt[r], 1, n, (r - l + 1) / 2));
}
