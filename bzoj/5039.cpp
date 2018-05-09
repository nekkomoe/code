#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

typedef long long ll;

ll sum[N * 8], mul[N * 8], add[N * 8], p;

int n, m;

#define lc (id << 1)

#define rc (id << 1 | 1)

void push(int id, int l, int r) {
    if(id[mul] != 1) {
        id[mul] %= p;
        id[sum] = id[sum] * id[mul] % p;
        lc[mul] = lc[mul] * id[mul] % p;
        lc[add] = lc[add] * id[mul] % p;
        rc[mul] = rc[mul] * id[mul] % p;
        rc[add] = rc[add] * id[mul] % p;
        id[mul] = 1;
    }
    if(id[add]) {
        id[add] %= p;
        id[sum] = (id[sum] + (r - l + 1) * id[add]) % p;
        lc[add] = (lc[add] + id[add]) % p;
        rc[add] = (rc[add] + id[add]) % p;
        id[add] = 0;
    }
}

void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r);
    id[sum] = (lc[sum] + rc[sum]) % p;
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    id[mul] = 1;
    if(l == r) {
        scanf("%lld", &id[sum]);
        id[sum] %= p;
    } else {
        build(lc, l, mid);
        build(rc, mid + 1, r);
        update(id ,l, r);
    }
}

void modify_mul(int id, int l, int r, int ql, int qr, ll v) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) id[mul] = v;
    else modify_mul(lc, l, mid, ql, qr, v), modify_mul(rc, mid + 1, r, ql, qr, v), update(id, l, r);
}

void modify_add(int id, int l, int r, int ql, int qr, ll v) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) id[add] = v;
    else modify_add(lc, l, mid, ql, qr, v), modify_add(rc, mid + 1, r, ql, qr, v), update(id, l, r);
}

ll query_sum(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id, l, r);
    if(l > qr || r < ql) return 0;
    if(ql <= l && r <= qr) return id[sum] % p;
    else return (query_sum(lc, l, mid, ql, qr) + query_sum(rc, mid + 1, r, ql, qr)) % p;
}

int main() {
    scanf("%d%lld", &n, &p);
    build(1, 1, n);
    scanf("%d", &m);
    for(int i = 1, op, l, r ; i <= m ; ++ i) {
        ll v;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d%lld", &l, &r, &v);
            modify_mul(1, 1, n, l, r, v % p);
        } else if(op == 2) {
            scanf("%d%d%lld", &l, &r, &v);
            modify_add(1, 1, n, l, r, v % p);
        } else {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query_sum(1, 1, n, l, r) % p);
        }
    }
    return 0;
}
