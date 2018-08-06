#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long ll;

const int N = 200010 * 8;

int T;

double tag[N], x[N], y[N];

#define lc (id << 1)

#define rc (id << 1 | 1)

void push(int id) {
    if(tag[id]) {
        double x = :: x[id], y = :: y[id], c = tag[id];
        :: x[id] = cos(c) * x + sin(c) * y;
        :: y[id] = cos(c) * y - sin(c) * x;
        tag[lc] += tag[id];
        tag[rc] += tag[id];
        tag[id] = 0;
    }
}

void update(int id) {
    push(lc), push(rc);
    x[id] = x[lc] + x[rc], y[id] = y[lc] + y[rc];
}

void modify(int id, int l, int r, int ql, int qr, double c) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        tag[id] += c;
    } else if(!(l > qr || r < ql)) {
        modify(lc, l, mid, ql, qr, c);
        modify(rc, mid + 1, r, ql, qr, c);
        update(id);
    }
}

double query(int id, int l, int r, int ql, int qr) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        return y[id];
    } else if(l > qr || r < ql) {
        return 0;
    } else {
        return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
    }
}

void init() {
    memset(tag, 0, sizeof tag), memset(x, 0, sizeof x), memset(y, 0, sizeof y);
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        double a;
        scanf("%lf", &a);
        x[id] = sin(a), y[id] = cos(a);
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        update(id);
    }
}

int n, m;

void sol() {
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for(int i = 1 ; i <= m ; ++ i) {
        int op, l, r; double c;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            scanf("%lf", &c);
            modify(1, 1, n, l, r, c);
        } else {
            printf("%.3lf\n", query(1, 1, n, l, r));
        }
    }
}

int main() {
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++ i) printf("Case #%d:\n", i), init(), sol();
}
