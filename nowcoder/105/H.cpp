#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>
 
using namespace std;
 
int n, m;
 
const int N = 1e5 + 10;
 
typedef long long ull;
 
ull bt[N * 10], tag[N * 10];
 
#define lc (id << 1)
 
#define rc (id << 1 | 1)
 
void update(int id) {
    if(id) {
        bt[id] = bt[lc] | bt[rc];
    }
}
 
void push(int id) {
    if(id && tag[id]) {
        tag[lc] |= tag[id], tag[rc] |= tag[id];
        bt[id] |= tag[id];
        tag[id] = 0;
        tag[0] = 0;
    }
}
 
void modify(int id, int l, int r, int ql, int qr, int c) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql > r || qr < l) return ;
    if(ql <= l && r <= qr) {
        tag[id] |= 1ll << c;
        return ;
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, c);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, c);
    } else {
        modify(lc, l, mid, ql, mid, c);
        modify(rc, mid + 1, r, mid + 1, qr, c);
    }
    push(lc), push(rc);
    update(id);
}
 
ull query(int id, int l, int r, int ql, int qr) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql > r || qr < l) {
        return 0;
    } else if(ql <= l && r <= qr) {
        return bt[id];
    } else if(qr <= mid) {
        return query(lc, l, mid, ql, qr);
    } else if(ql >= mid + 1) {
        return query(rc, mid + 1, r, ql, qr);
    } else {
        return query(lc, l, mid, ql, mid) | query(rc, mid + 1, r, mid + 1, qr);
    }
}
 
int cnt(ull x) {
    int res = 0;
    while(x) ++ res, x -= x & -x;
    return res;
}
 
void sol() {
    memset(bt, 0, sizeof bt);
    memset(tag, 0, sizeof tag);
    for(int i = 1, op, l, r, c ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1) {
            scanf("%d", &c);
            modify(1, 1, n, l, r, c);
        } else {
            printf("%d\n", cnt(query(1, 1, n, l, r)));
        }
    }
}
 
int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        sol();
    }
}
