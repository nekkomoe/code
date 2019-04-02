#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int mod = 998244353, N = 2e6 + 10;

int n, m;

ll f[N], g[N], sf[N], val, tag_f[N], tag_g[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void upd(int id) {
    sf[id] = (sf[lc] + sf[rc] + f[id]) % mod;
}

void push_f(int id, ll val) {
    (tag_f[id] *= val) %= mod;
    (f[id] *= val) %= mod;
    (sf[id] *= val) %= mod;
}

void push_g(int id, ll val) {
    (tag_g[id] *= val) %= mod;
    (g[id] *= val) %= mod;
}

void push(int id) {
    if(tag_f[id] != 1) {
        push_f(lc, tag_f[id]);
        push_f(rc, tag_f[id]);
        tag_f[id] = 1;
    }

    if(tag_g[id] != 1) {
        push_g(lc, tag_g[id]);
        push_g(rc, tag_g[id]);
        tag_g[id] = 1;
    }
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    g[id] = tag_f[id] = tag_g[id] = 1;
    if(l == r) {
        return ;
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
    }
}

void modify(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id);
    if(ql == l && r == qr) {
        (f[id] += val) %= mod;
        push_f(lc, 2), push_f(rc, 2);
    } else {
        (g[id] += val) %= mod;
        if(qr <= mid) {
            modify(lc, l, mid, ql, qr);
            push(rc);
            (f[rc] += val - g[rc]) %= mod;
            (g[rc] += g[rc]) %= mod;
            push_f(rc << 1, 2), push_f(rc << 1 | 1, 2);
            push_g(rc << 1, 2), push_g(rc << 1 | 1, 2);
            upd(rc);
        } else if(ql >= mid + 1) {
            modify(rc, mid + 1, r, ql, qr);
            push(lc);
            (f[lc] += val - g[lc]) %= mod;
            (g[lc] += g[lc]) %= mod;
            push_f(lc << 1, 2), push_f(lc << 1 | 1, 2);
            push_g(lc << 1, 2), push_g(lc << 1 | 1, 2);
            upd(lc);
        } else {
            modify(lc, l, mid, ql, mid), modify(rc, mid + 1, r, mid + 1, qr);
        }
    }
    upd(id);
}

int main() {
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    val = 1;
    while(m --) {
        int op, l, r; scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &l, &r);
            modify(1, 1, n, l, r);
            (val *= 2) %= mod;
        } else {
            printf("%lld\n", (sf[1] % mod + mod) % mod);
        }
    }
}
