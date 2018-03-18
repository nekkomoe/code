#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 200010;

struct P { int x, y; } sta[N], query[N];

struct L { P p; int l, r; } a[N];

vector<P> p[N * 4];

bool operator < (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }

int t;

ll ans[N];

ll cross(P a, P b) { return (ll) a.x * b.y - (ll) b.x * a.y; }

ll dot(P a, P b) { return (ll) a.x * b.x + (ll) a.y * b.y; }

P operator - (P a, P b) { return (P) {a.x - b.x, a.y - b.y}; }

void ins(int id, int l, int r, int ql, int qr, P p) {
    if(ql <= l && r <= qr) :: p[id].push_back(p);
    else if(!(ql > r || qr < l)) {
        int mid = (l + r) >> 1;
        ins(id << 1, l, mid, ql, qr, p), ins(id << 1 | 1, mid + 1, r, ql, qr, p);
    }
}

void dfs(int id, int l, int r) {
    if(l < r) {
        int mid = (l + r) >> 1;
        dfs(id << 1, l, mid), dfs(id << 1 | 1, mid + 1, r);
    }
    if(p[id].empty()) return ;
    sort(p[id].begin(), p[id].end());
    t = 0; for(vector<P> :: iterator it = p[id].begin() ; it != p[id].end() ; sta[++ t] = *(it ++))
        while(t >= 2 && cross(sta[t] - sta[t - 1], *it - sta[t - 1]) >= 0) -- t;
    for(int i = l ; i <= r ; ++ i) {
        if(query[i].x) {
            for(int l = 0, r = t ; l <= r ; ) {
                int len = (r - l) / 3, m1 = l + len, m2 = r - len;
                ll s1 = dot(query[i], sta[m1]), s2 = dot(query[i], sta[m2]);
                if(s1 > s2) r = m2 - 1, ans[i] = max(ans[i], s1);
                else l = m1 + 1, ans[i] = max(ans[i], s2);
            }
        }
    }
}

int main() {
    int n, op, x, y, m = 0;
    scanf("%d", &n);  
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &op, &x); if(op != 2) scanf("%d", &y);
        if(op == 1) a[++ m] = (L) { (P) {x, y}, i, n };
        if(op == 2) a[x].r = i;
        if(op == 3) query[i] = (P) {x, y};
    }
    for(int i = 1 ; i <= m ; ++ i) ins(1, 1, n, a[i].l, a[i].r, a[i].p);
    dfs(1, 1, n);
    for(int i = 1 ; i <= n ; ++ i) if(query[i].x) printf("%lld\n", ans[i]);
}
