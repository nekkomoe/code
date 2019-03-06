#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
char s[N];
int n, ans, p, q, np, nq, ch[N][26], pre[N], len[N], sz[N], tmp[N], bak[N], last = 1, cnt = 1, pos[N];
int nd(int l) { return len[++ cnt] = l, cnt; }
void ins(int c, int id) {
    pre[last = np = nd(len[p = last] + 1)] = 1, sz[np] = 1, pos[np] = id;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq, pos[nq] = pos[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}
int rt[N], lc[N * 20], rc[N * 20], nd_cnt, f[N], top[N];
void modify(int &x, int l, int r, int pos) {
    if(!x) x = ++ nd_cnt;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) modify(lc[x], l, mid, pos);
    else modify(rc[x], mid + 1, r, pos);
}
int ask(int x, int l, int r, int ql, int qr) {
    if(!x || ql > qr) return 0;
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) return 1;
    else if(qr <= mid) return ask(lc[x], l, mid, ql, qr);
    else if(ql >= mid + 1) return ask(rc[x], mid + 1, r, ql, qr);
    else return ask(lc[x], l, mid, ql, mid) || ask(rc[x], mid + 1, r, mid + 1, qr);
}
int merge(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ nd_cnt;
    lc[z] = merge(lc[x], lc[y]);
    rc[z] = merge(rc[x], rc[y]);
    return z;
}

int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a', i), modify(rt[last], 1, n, i);
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i > 1 ; -- i) rt[pre[bak[i]]] = merge(rt[pre[bak[i]]], rt[bak[i]]);
    for(int i = 2 ; i <= cnt ; ++ i) {
        int u = bak[i], fa = pre[u];
        if(fa == 1) {
            f[u] = 1, top[u] = u;
        } else {
            int x = ask(rt[top[fa]], 1, n, pos[u] - len[u] + len[top[fa]], pos[u] - 1);
            if(x) {
                f[u] = f[fa] + 1, top[u] = u;
            } else {
                f[u] = f[fa], top[u] = top[fa];
            }
        }
        ans = max(ans, f[u]);
    }
    printf("%d\n", ans);
}
