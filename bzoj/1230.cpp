#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, m;
int sum[N * 4], tag[N * 4];
#define lc (id << 1)
#define rc (id << 1 | 1)
void push(int id, int l, int r) {
    if(tag[id]) {
        tag[lc] ^= 1, tag[rc] ^= 1, tag[id] = 0;
        sum[id] = r - l + 1 - sum[id];
    }
}
void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] + sum[rc];
}
void modify(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) tag[id] ^= 1;
    else if(qr <= mid) modify(lc, l, mid, ql, qr), update(id, l, r);
    else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr), update(id, l, r);
    else modify(lc, l, mid, ql, mid), modify(rc, mid + 1, r, mid + 1, qr), update(id, l, r);
}
int query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) return sum[id];
    else if(qr <= mid) return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
    else return query(lc, l, mid, ql, mid) + query(rc, mid + 1, r, mid + 1, qr);
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, op, l, r ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 0) modify(1, 1, n, l, r);
        else printf("%d\n", query(1, 1, n, l, r));
    }
}
