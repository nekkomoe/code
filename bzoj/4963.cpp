#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10, SEGNODE = N * 100;
typedef pair<int, int> pii;

int n, mxn;

// segment tree
pii val[SEGNODE];
pii operator + (pii a, pii b) {
    return pii(max(a.first, b.first), max(a.second, b.second));
}
int lc[SEGNODE], rc[SEGNODE], WAY[SEGNODE], tot;
pii ask(int x, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    if(!x) return pii();
    else if(l == r) return val[x];
    else if(pos <= mid) return ask(lc[x], l, mid, pos) + val[x];
    else return ask(rc[x], mid + 1, r, pos) + val[x];
}
int modify(int x, int l, int r, int ql, int qr, pii p) {
    if(ql > r || qr < l || ql > qr) return x;
    int mid = (l + r) >> 1, res = x == 0 || WAY[x] != n ? ++ tot : x;
    WAY[res] = n;
    lc[res] = lc[x], rc[res] = rc[x], val[res] = val[x];
    if(ql <= l && r <= qr) {
        val[res] = val[res] + p;
    } else {
        lc[res] = modify(lc[x], l, mid, ql, qr, p);
        rc[res] = modify(rc[x], mid + 1, r, ql, qr, p);
    }
    return res;
}

// lct
int fa[N], ch[N][2], root[N], R[N];
int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}
int isrig(int x) {
    return ch[fa[x]][1] == x;
}
void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x);
    if(isroot(y)) {
        R[x] = R[y];
        R[y] = 0;
    } else {
        ch[z][isrig(y)] = x;
    }
    fa[x] = z;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
}
void splay(int x) {
    for( ; !isroot(x) ; rot(x)) {
        if(!isroot(fa[x])) {
            rot(isrig(fa[x]) == isrig(x) ? fa[x] : x);
        }
    }
}
int len[N];
void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x]) {
        splay(x);
        if(ch[x][1]) {
            R[ch[x][1]] = R[x];
        }
        root[n] = modify(root[n], 1, mxn, 1, R[x] - len[x], pii(len[x], 0));
        root[n] = modify(root[n], 1, mxn, max(1, R[x] - len[x] + 1), R[x], pii(0, R[x]));
        ch[x][1] = y;
        if(!fa[x]) R[x] = n;
    }
}

// sam
char str[N];
namespace SAM {
    int p, q, np, nq, ch[N][26], last = 1, cnt = 1, pre[N];
    int nd(int l) { return len[++ cnt] = l, cnt; }
    void ins(int c) {
        last = np = nd(len[p = last] + 1);
        while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
        if(p) {
            int q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                nq = nd(len[p] + 1);
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                
                pre[nq] = fa[nq] = pre[q];
                splay(q);
                R[nq] = R[q];
                access(nq);
                pre[q] = fa[q] = pre[np] = fa[np] = nq, R[np] = n;
                
                while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            } else {
                pre[np] = fa[np] = q, access(np);
            }
        } else {
            pre[np] = 1;
            fa[np] = 1, access(np);
        }
    }
}

int lastans;

int main() {
    scanf("%s", str + 1);
    int len = strlen(str + 1);
    int m; scanf("%d", &m);
    mxn = len + m;
    while(len --) {
        ++ n;
        root[n] = root[n - 1];
        SAM :: ins(str[n] - 'a');
    }
    while(m --) {
        int op; scanf("%d", &op);
        if(op == 1) {
            char str[5]; scanf("%s", str);
            char c = (str[0] - 'a' + lastans) % 26;
            ++ n;
            root[n] = root[n - 1];
            SAM :: ins(c);
        } else {
            int l, r; scanf("%d%d", &l, &r);
            l = ((l - 1 + lastans) % n) + 1;
            r = ((r - 1 + lastans) % n) + 1;
            pii res = ask(root[r], 1, mxn, l);
            printf("%d\n", lastans = max(res.first, res.second - l + 1));
        }
    }
}
