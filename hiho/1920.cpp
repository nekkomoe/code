// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
__int128 ans;

struct P {
    int c;
    ll d[2];
    ll mn[2], mx[2];
} p[N];

int n, root, lc[N], rc[N], D;
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
        p[res].mn[j] = p[res].d[j];
        p[res].mx[j] = p[res].d[j];
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

__int128 sqr(__int128 x) {
    return x * x;
}

__int128 calc(__int128 x1, __int128 y1, __int128 x2, __int128 y2) {
    return sqr(x1 - x2) + sqr(y1 - y2) + (x1 - x2) * (y1 - y2);
}

void print(__int128 x) {
    if(!x) return ;
    print(x / 10);
    putchar(x % 10 + '0');
}

int getmx(P a, P b) {

    ll pos[4][2] = {
        { b.mn[0], b.mn[1] },
        { b.mn[0], b.mx[1] },
        { b.mx[0], b.mn[1] },
        { b.mx[0], b.mx[1] },
    };

    for(int i = 0 ; i < 4 ; ++ i) {
        if(calc(pos[i][0], pos[i][1], a.d[0], a.d[1]) > ans) {
            return 0;
        }
    }

    return 1;
}

void ask(int u, P a) {
    if(!u || getmx(a, p[u])) return ;
    if(a.c != p[u].c) ans = max(ans, calc(a.d[0], a.d[1], p[u].d[0], p[u].d[1]));
    ask(lc[u], a), ask(rc[u], a);
}

int main() {

    // cout << calc(1e9, 1e9, -1e9, -1e9) << endl;

    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        ll x, y; int c;
        scanf("%lld%lld%d", &x, &y, &c);
        p[i].d[0] = x;
        p[i].d[1] = y;
        p[i].c = c;
        if(p[i].c != p[1].c) {
            ans = calc(p[1].d[0], p[1].d[1], p[i].d[0], p[i].d[1]);
        }
    }
    root = build(1, n);
    for(int i = 1 ; i <= n ; ++ i) {
        ask(root, p[i]);
    }
    if(ans == 0) {
        puts("0");
        return 0;
    } else if(ans < 0) {
        putchar('-');
        ans = -ans;
    }
    print(ans);
}
