// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
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

void cdq(int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) return ;
    
    top_pts = top_que = 0;
    
    for(int i = l ; i <= mid ; ++ i)
        if(a[i].id == 0)
            pts[++ top_pts] = a[i];
    sort(pts + 1, pts + 1 + top_pts, cmpy);
    
    for(int i = mid + 1 ; i <= r ; ++ i)
        if(a[i].id != 0)
            que[++ top_que] = a[i];
    sort(que + 1, que + 1 + top_que, cmpy);
    
    ll sum = 0;
    for(int i = 1, j = 1 ; i <= top_que ; ++ i) {
        while(j <= top_pts && pts[j].y <= que[i].y) {
            sum += pts[j ++].p;
        }
        ans[que[i].id] += que[i].p * sum;
    }
    
    cdq(l, mid), cdq(mid + 1, r);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        ++ tot;
        scanf("%lld%lld%lld", &a[tot].x, &a[tot].y, &a[tot].p);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        ll x1, y1, x2, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        a[++ tot] = (P) { x2, y2, 1, i };
        a[++ tot] = (P) { x1 - 1, y1 - 1, 1, i };
        a[++ tot] = (P) { x2, y1 - 1, -1, i };
        a[++ tot] = (P) { x1 - 1, y2, -1, i };
    }
    
    sort(a + 1, a + 1 + tot, cmpx);
    cdq(1, tot);
    for(int i = 1 ; i <= m ; ++ i)
        printf("%lld\n", ans[i]);
} 

