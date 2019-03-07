#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;

char s[N];
int p, q, np, nq, samch[N][2], last = 1, cnt = 1, pre[N], len[N], pos[N];
int n, Q, ans[N];

int nd(int l) { return len[++ cnt] = l, cnt; } 
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1;
    while(p && !samch[p][c]) samch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = samch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(samch[nq], samch[q], sizeof samch[q]);
            while(p && samch[p][c] == q) samch[p][c] = nq, p = pre[p];
        }
    }
}

struct QUES { int l, id; };
vector<QUES> ques[N];

namespace SEGTREE {
    int mx[N];
    #define lc (id << 1)
    #define rc (id << 1 | 1)
    void upd(int id) {
        mx[id] = max(mx[lc], mx[rc]);
    }
    void modify(int id, int l, int r, int pos, int val) {
        int mid = (l + r) >> 1;
        if(l == r) {
            mx[id] = max(mx[id], val);
            return ;
        } else if(pos <= mid) {
            modify(lc, l, mid, pos, val);
        } else {
            modify(rc, mid + 1, r, pos, val);
        }
        upd(id);
    }
    int ask(int id, int l, int r, int ql, int qr) {
        int mid = (l + r) >> 1;
        if(ql <= l && r <= qr) {
            return mx[id];
        } else if(qr <= mid) {
            return ask(lc, l, mid, ql, qr);
        } else if(ql >= mid + 1) {
            return ask(rc, mid + 1, r, ql, qr);
        } else {
            return max(ask(lc, l, mid, ql, mid), ask(rc, mid + 1, r, mid + 1, qr));
        }
    }
}

int val[N], ch[N][2];
#define fa pre

int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
int isrig(int x) { return ch[fa[x]][1] == x; }

void upd(int x) {
    if(!isroot(x)) upd(fa[x]);
    val[ch[x][0]] = val[x];
    val[ch[x][1]] = val[x];
}

void rot(int x) {
    int f = fa[x], k = isrig(x);
    fa[x] = fa[f]; if(!isroot(f)) ch[fa[f]][isrig(f)] = x;
    fa[ch[f][k] = ch[x][!k]] = f;
    fa[ch[x][!k] = f] = x;
}

void splay(int x) {
    for(upd(x) ; !isroot(x) ; rot(x))
        if(!isroot(fa[x]))
            rot(isrig(x) == isrig(fa[x]) ? fa[x] : x);
}

void vist(int x) {
    for(int t = 0 ; x ; x = fa[x]) {
        splay(x);
        if(val[x]) {
            SEGTREE :: modify(1, 1, n, val[x], len[x]);
        }
        ch[x][1] = t, t = x;
    }
}

int main() {
    freopen("history.in", "r", stdin);
    freopen("history.out", "w", stdout);

    scanf("%d%d%s", &n, &Q, s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - '0'), pos[i] = last;
    for(int i = 1 ; i <= Q ; ++ i) {
        int l, r; scanf("%d%d", &l, &r);
        ques[r].push_back((QUES) { l, i });
    }

    for(int i = 1 ; i <= n ; ++ i) {
        int p = pos[i]; vist(p), splay(p), val[p] = i;
        for(auto q: ques[i]) {
            ans[q.id] = SEGTREE :: ask(1, 1, n, q.l, n);
        }
    }

    for(int i = 1 ; i <= Q ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
