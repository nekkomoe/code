#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, m, last[N], pre[N], a[N];

void add(int i, int c) { for( ; i ; i -= i & -i) a[i] += c; }

int query(int i, int &c) { for( ; i <= n ; i += i & -i) c += a[i]; }

struct Q { int l, r, id, ans; } q[N];

bool cmp1(Q x, Q y) { return x.r < y.r || (x.r == y.r && x.l < y.l); }

bool cmp2(Q x, Q y) { return x.id < y.id; }

int main() {
    scanf("%d%*d%d", &n, &m);
    for(int i = 1, c ; i <= n ; ++ i) scanf("%d", &c), pre[i] = last[c], last[c] = i;
    for(int i = 1, l, r ; i <= m ; ++ i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m, cmp1);
    for(int i = 1, t = 1 ; i <= m ; ++ i) {
        add(pre[pre[i]], -1), add(pre[i], 1);
        while(q[t].r == i) query(q[t].l, q[t].ans), ++ t;
    }
    sort(q + 1, q + 1 + m, cmp2);
    for(int i = 1 ; i <= m ; ++ i) printf("%d\n", q[i].ans);
}
