#include "bits/stdc++.h"
using namespace std;
const int N = (5e5 + 10) * 10;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline int operator ! () {
        int c = xchar(); int x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (int x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(int x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int n, m, tag[N], mn[N], sumand[N], sumor[N];

#define lc (id << 1)
#define rc (id << 1 | 1)

void push(int id) {
    if(tag[id] != -1) {
        mn[id] = sumand[id] = sumor[id] = tag[id];
        tag[lc] = tag[rc] = tag[id];
        tag[id] = -1;
    }
}

void update(int id) {
    push(id), push(lc), push(rc);
    mn[id] = min(mn[lc], mn[rc]);
    sumand[id] = sumand[lc] & sumand[rc];
    sumor[id] = sumor[lc] | sumor[rc];
}

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    tag[id] = -1;
    if(l == r) {
        sumand[id] = sumor[id] = mn[id] = io();
    } else {
        build(lc, l, mid), build(rc, mid + 1, r);
        mn[id] = min(mn[lc], mn[rc]);
        sumand[id] = sumand[lc] & sumand[rc];
        sumor[id] = sumor[lc] | sumor[rc];
    }
}

void modify(int id, int l, int r, int ql, int qr, int x, int type) {
    push(id);
    int mid = (l + r) >> 1;

    if((
        type == 0 && (sumor[id] & x) == sumor[id]
        ) || (
        type == 1 && (sumand[id] | x) == sumand[id]
        )) {
        return ;
    }

    if(l == r ||
        (ql <= l && r <= qr
        && ((type == 0 && (sumand[id] & x) == (sumor[id] & x))
         || (type == 1 && (sumand[id] | x) == (sumor[id] | x))))) {

        if(type == 0) tag[id] = x & mn[id];
        else tag[id] = x | mn[id];
    } else if(qr <= mid) modify(lc, l, mid, ql, qr, x, type), update(id);
    else if(ql >= mid + 1) modify(rc, mid + 1, r, ql, qr, x, type), update(id);
    else modify(lc, l, mid, ql, mid, x, type), modify(rc, mid + 1, r, mid + 1, qr, x, type), update(id);
}

int query(int id, int l, int r, int ql, int qr) {
    push(id);
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return mn[id];
    else if(qr <= mid) return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1) return query(rc, mid + 1, r, ql, qr);
    else return min(query(lc, l, mid, ql, mid), query(rc, mid + 1, r, mid + 1, qr));
}

int main() {
    n = io(), m = io();
    build(1, 1, n);
    for(int i = 1, op, l, r, x ; i <= m ; ++ i) {
        op = io(), l = io(), r = io();
        if(op != 3) x = io();
        if(op == 1) {
            modify(1, 1, n, l, r, x, 0);
        } else if(op == 2) {
            modify(1, 1, n, l, r, x, 1);
        } else {
            io(query(1, 1, n, l, r));
        }
    }
}
