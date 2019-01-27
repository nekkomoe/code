%:pragma GCC optimize(2)
 
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
const int N = 1e5 + 10;
 
const int inf = 0x3f3f3f3f;
 
int n, m, q, a[N], b[N], c[N], sz;
 
int sum[N * 4], tag[N * 4];
 
struct MOD {
    int k, l, r;
} mod[N];
 
#define lc (id << 1)
 
#define rc (id << 1 | 1)
 
void push(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(tag[id] != inf) {
        tag[lc] = tag[id];
        tag[rc] = tag[id];
        sum[id] = (r - l + 1) * tag[id];
        tag[id] = inf;
    }
}
 
void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] + sum[rc];
}
 
 
void modify(int id, int l, int r, int ql, int qr, int v) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) tag[id] = v;
    else modify(lc, l, mid, ql, qr, v), modify(rc, mid + 1, r, ql, qr, v), update(id, l, r);
}
 
int query(int id, int l, int r, int ql, int qr) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(l > qr || r < ql) return 0;
    if(ql <= l && r <= qr) return sum[id];
    else return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
}
 
void bd(int id, int l, int r, int m) {
    int mid = (l + r) >> 1;
    if(l == r) {
        sum[id] = (c[l] > m);
        return;
    }
    bd(lc, l, mid, m);
    bd(rc, mid + 1, r, m);
    sum[id] = sum[lc] + sum[rc];
}
 
void build(int mid) {
    memset(sum, 0, sizeof(sum));
    memset(tag, 0x3f, sizeof(tag));
    bd(1, 1, n, mid);
}
 
bool check(int mid) {
    build(mid);
    for(int i = 1 ; i <= m ; ++ i) {
        int sum = query(1, 1, n, mod[i].l, mod[i].r);
        int len = mod[i].r - mod[i].l + 1;
        if(mod[i].k == 0) {
            modify(1, 1, n, mod[i].l, mod[i].l + (len - sum) - 1, 0);
            modify(1, 1, n, mod[i].l + (len - sum), mod[i].r, 1);
        } else {
            modify(1, 1, n, mod[i].l, mod[i].l + sum - 1, 1);
            modify(1, 1, n, mod[i].l + sum, mod[i].r, 0);
        }
    }
    return query(1, 1, n, q, q);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    sz = unique(b + 1, b + 1 + n) - b - 1;
    for(int i = 1 ; i <= n ; ++ i) {
        c[i] = lower_bound(b + 1, b + 1 + sz, a[i]) - b;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d", &mod[i].k, &mod[i].l, &mod[i].r);
    }
    scanf("%d", &q);
    int l = 1, r = sz, ans = -1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(check(m)) {
            l = m + 1;
        } else {
            r = m - 1;
            ans = m;
        }
    }
    printf("%d\n", b[ans]);
    return 0;
}
