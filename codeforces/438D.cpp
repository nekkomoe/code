#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n, m;

#define lc (id << 1)
#define rc (id << 1 | 1)

typedef long long ll;

ll sum[N * 10], mx[N * 10];

void update(int id) {
    sum[id] = sum[lc] + sum[rc];
    mx[id] = max(mx[lc], mx[rc]);
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        scanf("%lld", &sum[id]), mx[id] = sum[id];
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        update(id);
    }
}

void modify(int id, int l, int r, int pos, int val) {
    int mid = (l + r) >> 1;
    if(l == r) return sum[id] = mx[id] = val, void();
    else if(pos <= mid) modify(lc, l, mid, pos, val);
    else modify(rc, mid + 1, r, pos, val);
    update(id);
}

void modify(int id, int l, int r, int ql, int qr, ll mod) {
    int mid = (l + r) >> 1;
    if(ql > r || qr < l) return ;
    if(l == r) {
        sum[id] %= mod, mx[id] %= mod;
    } if(mx[id] < mod) {
        return ;
    } else {
        modify(lc, l, mid, ql, qr, mod);
        modify(rc, mid + 1, r, ql, qr, mod);
        update(id);
    }
}


ll query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return sum[id];
    } else if(ql > r || qr < l) {
        return 0;
    } else {
        return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
    }
}

void sol() {
    memset(sum, 0, sizeof sum), memset(mx, 0, sizeof mx);
    build(1, 1, n);
    for(int i = 1, op, l, r, k, x ; i <= m ; ++ i) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        } else if(op == 2) {
            scanf("%d%d%d", &l, &r, &x);
            modify(1, 1, n, l, r, x);
        } else {
            scanf("%d%d", &k, &x);
            modify(1, 1, n, k, x);
        }
    }
}

int main() { while(scanf("%d%d", &n, &m) == 2) sol(); }

