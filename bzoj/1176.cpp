#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m;

struct P {
    ll x, y, p;
    int id;
} a[N * 5];

bool cmpx(P a, P b) {
    if(a.x == b.x) return a.id < b.id;
    return a.x < b.x;
}

bool cmpy(P a, P b) {
    if(a.y == b.y) return a.id < b.id;
    return a.y < b.y;
}

int tot; ll ans[N];

P pts[N * 5]; int top_pts;
P que[N * 5]; int top_que;

int W;
const int T = 2000000 + 10;
ll bit[T];

void add(int x, ll y) {
    for( ; x <= W ; x += x & -x)
        bit[x] += y;
}

void cls(int x) {
    for( ; x <= W ; x += x & -x)
        bit[x] = 0;
}

ll ask(int x) {
    ll res = 0;
    for( ; x ; x -= x & -x)
        res += bit[x];
    return res;
}

void cdq(int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) return ;

    top_pts = top_que = 0;

    for(int i = l ; i <= mid ; ++ i)
        if(a[i].id == 0)
            pts[++ top_pts] = a[i];
    sort(pts + 1, pts + 1 + top_pts, cmpx);

    for(int i = mid + 1 ; i <= r ; ++ i)
        if(a[i].id != 0)
            que[++ top_que] = a[i];
    sort(que + 1, que + 1 + top_que, cmpx);

    for(int i = 1, j = 1 ; i <= top_que ; ++ i) {
        while(j <= top_pts && pts[j].x <= que[i].x) {
            add(pts[j].y, pts[j].p);
            ++ j;
        }
        ans[que[i].id] += que[i].p * ask(que[i].y);
    }

    for(int j = 1 ; j <= top_pts ; ++ j) {
        cls(pts[j].y);
    }

    cdq(l, mid), cdq(mid + 1, r);
}

int main() {
    scanf("%*d%d", &W);
    int op;
    while(scanf("%d", &op) == 1) {
        if(op == 1) {
            ++ tot;
            scanf("%lld%lld%lld", &a[tot].x, &a[tot].y, &a[tot].p);
        } else if(op == 2) {
            ++ m;
            ll x1, y1, x2, y2;
            scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
            a[++ tot] = (P) { x2, y2, 1, m };
            a[++ tot] = (P) { x1 - 1, y1 - 1, 1, m };
            a[++ tot] = (P) { x2, y1 - 1, -1, m };
            a[++ tot] = (P) { x1 - 1, y2, -1, m };
        } else if(op == 3) {
            break;
        }

    }

    cdq(1, tot);

    for(int i = 1 ; i <= m ; ++ i)
        printf("%lld\n", ans[i]);
} 
