// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;

struct CIRC {
    int id;
    ll x, y, r;
} circ[N];
bool operator < (CIRC a, CIRC b) {
    return a.r == b.r ? a.id < b.id : a.r > b.r;
}

struct P {
    int id;
    ll d[2], r;
    ll mn[2], mx[2];
} p[N];

int n, ans[N], root, lc[N], rc[N], D;
bool cmp(P a, P b) {
    return a.d[D] < b.d[D];
}

int build(int l, int r) {
    D ^= 1;
    int res = (l + r) >> 1;
    nth_element(p + l, p + res, p + r + 1, cmp);

    if(l <= res - 1) {
        lc[res] = build(l, res - 1);
    }
    if(res + 1 <= r) {
        rc[res] = build(res + 1, r);
    }

    for(int j = 0 ; j < 2 ; ++ j) {
        p[res].mn[j] = p[res].d[j] - p[res].r;
        p[res].mx[j] = p[res].d[j] + p[res].r;
        if(lc[res]) {
            p[res].mn[j] = min(p[res].mn[j], p[lc[res]].mn[j]);
            p[res].mx[j] = max(p[res].mx[j], p[lc[res]].mx[j]);
        }
        if(rc[res]) {
            p[res].mn[j] = min(p[res].mn[j], p[rc[res]].mn[j]);
            p[res].mx[j] = max(p[res].mx[j], p[rc[res]].mx[j]);
        }
    }

    return res;
}

ll sqr(ll x) {
    return x * x;
}

int check_outside(P a, P b) {
    if(b.mn[0] > a.d[0] + a.r || b.mx[0] < a.d[0] - a.r) return 1;
    if(b.mn[1] > a.d[1] + a.r || b.mx[1] < a.d[1] - a.r) return 1;
    return 0;
}

int check_inj(P a, P b) {
    return sqr(a.d[0] - b.d[0]) + sqr(a.d[1] - b.d[1]) <= sqr(a.r + b.r);
}

void ask(int u, P a) {

    if(check_outside(a, p[u])) {
        return ;
    }

    if(!ans[p[u].id] && check_inj(a, p[u])) {
        ans[p[u].id] = a.id;
    }

    if(lc[u]) {
        ask(lc[u], a);
    }
    if(rc[u]) {
        ask(rc[u], a);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld%lld", &circ[i].x, &circ[i].y, &circ[i].r);
        circ[i].id = i;

        p[i].d[0] = circ[i].x;
        p[i].d[1] = circ[i].y;
        p[i].r = circ[i].r;
        p[i].id = circ[i].id;
    }
    root = build(1, n);
    sort(circ + 1, circ + 1 + n);

    for(int i = 1 ; i <= n ; ++ i) {
        P p;
        p.d[0] = circ[i].x, p.d[1] = circ[i].y;
        p.r = circ[i].r, p.id = circ[i].id;

        if(!ans[p.id]) {
            ask(root, p);
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", ans[i]);
    }
}
