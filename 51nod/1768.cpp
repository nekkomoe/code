#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll inf = 1ll << 60, N = 1e5 + 10;
typedef pair<ll, ll> p;
p operator + (p a, p b) {
    return p(a.first + b.first, min(a.second, a.first + b.second));
}

int n, m;
struct QUERY {
    int op, l, r, p, x;
} the_query[N];

struct P {
    int mn[2], mx[2], d[2], lc, rc;
    p val, tag;
    P() {
        tag = p(0, inf);
    }
} pts[N];
int tot;
P get(int x, int y, ll v) {
    P res;
    res.mn[0] = res.mx[0] = res.d[0] = x;
    res.mn[1] = res.mx[1] = res.d[1] = y;
    res.val = p(v, v);
    return res;
}

ll a[N], s[N];

int D, rt;

bool cmp(P a, P b) {
    return a.d[D] < b.d[D] || (a.d[D] == b.d[D] && a.d[!D] < b.d[!D]);
}


void upd(int x, int lc, int rc) {
    for(int j = 0 ; j < 2 ; ++ j) {
        if(lc) {
            for(int i = 0 ; i < 2 ; ++ i) {
                pts[x].mn[i] = min(pts[x].mn[i], pts[lc].mn[i]);
                pts[x].mx[i] = max(pts[x].mx[i], pts[lc].mx[i]);
            }
        }
        swap(lc, rc);
    }
}
void build(int &x, int l, int r, int rev) {
    D = rev;
    x = (l + r) >> 1;
    nth_element(pts + l, pts + x, pts + r + 1, cmp);
    if(l <= x - 1) {
        build(pts[x].lc, l, x - 1, !rev);
    }
    if(x + 1 <= r) {
        build(pts[x].rc, x + 1, r, !rev);
    }
    upd(x, pts[x].lc, pts[x].rc);
}

void push(int x) {
    int lc = pts[x].lc, rc = pts[x].rc;
    for(int j = 0 ; j < 2 ; ++ j) {
        if(lc) {
            pts[lc].val = pts[lc].val + pts[x].tag;
            pts[lc].tag = pts[lc].tag + pts[x].tag;
        }
        swap(lc, rc);
    }
    pts[x].tag = p(0, inf);
}

void modify(int x, int x0, int y0, int x1, int y1, p tmp) {
    if(x0 > pts[x].mx[0] || x1 < pts[x].mn[0] || y0 > pts[x].mx[1] || y1 < pts[x].mn[1]) {
        return ;
    }
    if(x0 <= pts[x].mn[0] && pts[x].mx[0] <= x1 && y0 <= pts[x].mn[1] && pts[x].mx[1] <= y1) {
        pts[x].val = pts[x].val + tmp;
        pts[x].tag = pts[x].tag + tmp;
        return ;
    }
    if(x0 <= pts[x].d[0] && pts[x].d[0] <= x1 && y0 <= pts[x].d[1] && pts[x].d[1] <= y1) {
        pts[x].val = pts[x].val + tmp;
    }
    push(x);
    if(pts[x].lc) {
        modify(pts[x].lc, x0, y0, x1, y1, tmp);
    }
    if(pts[x].rc) {
        modify(pts[x].rc, x0, y0, x1, y1, tmp);
    }
}

p ask(int x, int x0, int y0, int rev) {
    if(pts[x].d[0] == x0 && pts[x].d[1] == y0) return pts[x].val;
    push(x);
    if(rev == 0) {
        if(x0 < pts[x].d[0] || (x0 == pts[x].d[0] && y0 < pts[x].d[1])) {
            return ask(pts[x].lc, x0, y0, !rev);
        } else {
            return ask(pts[x].rc, x0, y0, !rev);
        }
    } else {
        if(y0 < pts[x].d[1] || (y0 == pts[x].d[1] && x0 < pts[x].d[0])) {
            return ask(pts[x].lc, x0, y0, !rev);
        } else {
            return ask(pts[x].rc, x0, y0, !rev);
        }
    }
}

int main() {

//    freopen("data.in", "r", stdin);

    // freopen("ds.in", "r", stdin);
    // freopen("ds.out", "w", stdout);

    scanf("%d%d", &n, &m);

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    for(int i = 1 ; i <= m ; ++ i) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if(op == 1) {
            the_query[i].op = op;
            the_query[i].p = a;
            the_query[i].x = b;
        } else {
            the_query[i].op = op;
            the_query[i].l = a;
            the_query[i].r = b;
            pts[++ tot] = get(a, b, s[b] - s[a - 1]);
        }
    }

    build(rt, 1, tot, 0);

    for(int i = 1 ; i <= m ; ++ i) {
        int op = the_query[i].op;
        int pos = the_query[i].p;
        int x = the_query[i].x;
        int l = the_query[i].l;
        int r = the_query[i].r;
        if(op == 1) {
            modify(rt, 1, pos, pos, n, p(x - a[pos], x - a[pos]));
            a[pos] = x;
        } else {
            printf("%lld\n", ask(rt, l, r, 0).second);
        }
    }
}
