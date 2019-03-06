#include "bits/stdc++.h"

using namespace std;
 
const int N = 2e6 + 10;
 
char s[N];

int p, q, np, nq, ch[N][2], pre[N], len[N], sz[N], tmp[N], bak[N], last = 1, cnt = 1;

int n, m;

int nd(int l) { return len[++ cnt] = l, cnt; }
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1, sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

set<int> st[N];
struct P { int l, r, w; } dat[N], que[N]; int tot;
bool operator < (P a, P b) { return a.l > b.l; }
int a[N], ans[N];
void modify(int x, int y) { for( ; x <= n ; x += x & -x) a[x] = max(a[x], y); }
int ask(int x) { int res = 0; for( ; x ; x -= x & -x) res = max(res, a[x]); return res; }

int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - '0'), st[last].insert(i);
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i >= 2 ; -- i) {
        int x = bak[i], y = pre[x];
        if(st[y].size() < st[x].size()) swap(st[x], st[y]);
        for(int val: st[x]) {
            auto it = st[y].lower_bound(val);
            if(it != st[y].end()) dat[++ tot] = (P) { val, *it, len[y] };
            if(it != st[y].begin()) dat[++ tot] = (P) { *(-- it), val, len[y] };
        }
        for(int val: st[x]) st[y].insert(val);
    }
    for(int i = 1 ; i <= m ; ++ i) scanf("%d%d", &que[i].l, &que[i].r), que[i].w = i;
    sort(dat + 1, dat + 1 + tot), sort(que + 1, que + 1 + tot);
    for(int i = 1, j = 1 ; i <= m ; ++ i) {
        while(j <= tot && dat[j].l >= que[i].l) modify(dat[j].r, dat[j].w), ++ j;
        ans[que[i].w] = ask(que[i].r);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
