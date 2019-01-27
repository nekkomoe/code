%:pragma GCC optimize(2)
;
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
 
using namespace std;
 
const int N = 1100000;
 
typedef long long ll;
 
ll tag[N * 4], mx[N * 4], ans;
 
#define lc (id << 1)
 
#define rc (id << 1 | 1)
 
void push(int id) {
    if(tag[id]) {
        tag[lc] += tag[id];
        tag[rc] += tag[id];
        mx[id] += tag[id];
        tag[id] = 0;
    }
}
 
void update(int id) {
    push(id), push(lc), push(rc);
    mx[id] = max(mx[lc], mx[rc]);
}
 
void modify(int id, int l, int r, int ql, int qr, ll v) {
    push(id);
    int mid = (l + r) >> 1;
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) tag[id] += v;
    else modify(lc, l, mid, ql, qr, v), modify(rc, mid + 1, r, ql, qr, v), update(id);
}
 
int n, m, f[N], w[N], lst[N], nxt[N];
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &f[i]);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &w[i]);
    }
    for(int i = n ; i >= 1 ; -- i) {
        nxt[i] = lst[f[i]];
        lst[f[i]] = i;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(lst[i]) {
            if(!nxt[lst[i]]) modify(1, 1, n, lst[i], n, w[i]);
            else modify(1, 1, n, lst[i], nxt[lst[i]] - 1, w[i]);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        push(1);
        ans = max(ans, mx[1]);
        int t = nxt[i];
        if(t) {
            modify(1, 1, n, i, t - 1, -w[f[i]]);
            if(nxt[t]) modify(1, 1, n, t, nxt[t] - 1, w[f[i]]);
            else modify(1, 1, n, t, n, w[f[i]]);
        } else modify(1, 1, n, i, n, -w[f[i]]);
    }
    printf("%lld\n", ans);
    return 0;
}
