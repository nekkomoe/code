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
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;

const ll inf = 0x3f3f3f3f3f3f3f3fll;

const int N = 3e5 + 10;

int n; ll C, D, f[N], ans;

struct HQ {
    ll d, p, r, g;
} a[N];

bool operator < (HQ x, HQ y) {
    return x.d < y.d;
}

struct P {
    ll x, y, fafa;
    P(ll x = 0, ll y = 0): x(x), y(y) {}
} p[N], pt[N], sta[N];

P operator - (P a, P b) {
    return P(a.x - b.x, a.y - b.y);
}

ll cross(P a, P b) {
    return a.x * b.y - b.x * a.y;
}

void init() {
    memset(a, 0, sizeof a);
    memset(f, 0, sizeof f);
    memset(p, 0, sizeof p);
}

ll calc(int j, int i) {
    ll res = a[i].d * a[j].g + f[j] - (1 + a[j].d) * a[j].g + a[j].r - a[i].p;
    return res >= 0 ? res : -inf;
}

ll fk(P p, int i) {
    ll res = a[i].d * p.x + p.y - a[i].p;
    return res >= 0 ? res : -inf;
}

void cdq(int l, int r) {

    if(l == r) {
        if(f[l] >= 0) {
            p[l].x = a[l].g;
            p[l].y = f[l] - (1 + a[l].d) * a[l].g + a[l].r;
        }
        p[l].fafa = f[l];
    } else {
        int mid = (l + r) >> 1, L, R;

        cdq(l, mid);

        int tp = 0;
        for(int i = l ; i <= mid ; ++ i) {
            if(p[i].fafa < 0) continue;
            while(tp > 1 && cross(sta[tp] - sta[tp - 1], p[i] - sta[tp - 1]) >= 0) -- tp;
            sta[++ tp] = p[i];
        }

// cout << "tp = " << tp << endl;

#define DEBUG

// 不知道为啥要写暴力扫凸包，随机情况下凸包大小平均10左右

#ifdef DEBUG
        for(int i = mid + 1 ; i <= r ; ++ i) {
            for(int j = 1 ; j <= tp ; ++ j) {
                f[i] = max(f[i], fk(sta[j], i));
            }
        }
#else
        if(tp) {
            int _ = 1;
            for(int i = mid + 1 ; i <= r ; ++ i) {
                while(_ < tp && fk(sta[_], i) < fk(sta[_ + 1], i)) ++ _;
                f[i] = max(f[i], fk(sta[_], i));
            }
        }
#endif

        cdq(mid + 1, r);

        L = l, R = mid + 1;
        tp = l;
        while(L <= mid && R <= r) {
            if(p[L].x == p[R].x ? p[L].y < p[R].y : p[L].x < p[R].x) {
                pt[tp ++] = p[L ++];
            } else {
                pt[tp ++] = p[R ++];
            }
        }
        while(L <= mid) {
            pt[tp ++] = p[L ++];
        }
        while(R <= r) {
            pt[tp ++] = p[R ++];
        }
        for(int i = l ; i <= r ; ++ i) {
            p[i] = pt[i];
        }
    }
}

void sol() {
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld%lld%lld", &a[i].d, &a[i].p, &a[i].r, &a[i].g);
    }
    sort(a + 1, a + 1 + n);
    ans = f[0] = C;
    for(int i = 1 ; i <= n ; ++ i) {
        f[i] = calc(0, i);
    }

    cdq(1, n);
    for(int i = 1 ; i <= n ; ++ i) {
        if(f[i] >= 0) {
            ans = max(ans, f[i] + (D - a[i].d) * a[i].g + a[i].r);
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int T = 0;
    while(scanf("%d%lld%lld", &n, &C, &D) == 3 && (n || C || D)) {
        printf("Case %d: ", ++ T);
        init();
        sol();
    }
}

