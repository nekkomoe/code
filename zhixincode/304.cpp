#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;

int n, q, x, a[N], seq[N];
ll pre[2][N];
int ct[2];

int sum[N], tag[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id, int l, int r) {
    if(tag[id] != -1) {
        tag[lc] = tag[id], tag[rc] = tag[id];
        if(tag[id] == 0) {
            sum[id] = 0;
        } else {
            sum[id] = tag[id] * (r - l + 1);
        }
        tag[id] = -1;
    }
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    tag[id] = -1;
    if(l == r) {
        sum[id] = seq[l];
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        sum[id] = sum[lc] + sum[rc];
    }
}

void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    sum[id] = sum[lc] + sum[rc];
}

void ch(int id, int l, int r, int ql, int qr, int x) {
    if(ql > qr) return ;
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        tag[id] = x;
        return ;
    } else if(qr <= mid) {
        ch(lc, l, mid, ql, qr, x);
    } else if(ql >= mid + 1) {
        ch(rc, mid + 1, r, ql, qr, x);
    } else {
        ch(lc, l, mid, ql, mid, x);
        ch(rc, mid + 1, r, mid + 1, qr, x);
    }
    update(id, l, r);
}

int ask(int id, int l, int r, int ql, int qr) {
    if(ql > qr) return 0;
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(ql <= l && r <= qr) {
        return sum[id];
    } else if(qr <= mid) {
        return ask(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return ask(rc, mid + 1, r, ql, qr);
    } else {
        return ask(lc, l, mid, ql, mid) + ask(rc, mid + 1, r, mid + 1, qr);
    }
}

int main() {
    scanf("%d%d%d", &n, &q, &x);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        int ty = a[i] <= x;
        pre[ty][++ ct[ty]] = a[i];
        pre[ty][ct[ty]] += pre[ty][ct[ty] - 1];
        seq[i] = ty;
    }
    build(1, 1, n);
    for(int i = 1 ; i <= q ; ++ i) {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            int S1r = ask(1, 1, n, 1, r);
            int S1l = ask(1, 1, n, 1, l - 1);
            ll ans1 = pre[1][S1r] - pre[1][S1l];
            S1r = r - S1r;
            S1l = l - 1 - S1l;
            ll ans2 = pre[0][S1r] - pre[0][S1l];
            printf("%lld\n", ans1 + ans2);
        } else if(op == 2) {
            int Slr = ask(1, 1, n, l, r);
            ch(1, 1, n, l, l + Slr - 1, 1);
            ch(1, 1, n, l + Slr, r, 0);
        } else {
            int Slr = ask(1, 1, n, l, r);
            ch(1, 1, n, l, r - Slr, 0);
            ch(1, 1, n, r - Slr + 1, r, 1);
        }
    }
}
