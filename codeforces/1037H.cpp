#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;

char s[N];
int p, q, np, nq, ch[N][26], last = 1, cnt = 1, pre[N], len[N], bak[N], tmp[N];

int nd(int l) { return len[++ cnt] = l, cnt; } 
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1;
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

int n, m, pos[N], nd_cnt;

int rt[N], lc[N * 25], rc[N * 25];

void modify(int &x, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    if(!x) x = ++ nd_cnt;
    if(l == r) return ;
    if(pos <= mid) modify(lc[x], l, mid, pos);
    else modify(rc[x], mid + 1, r, pos);
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ nd_cnt;
    lc[z] = merge(lc[x], lc[y]);
    rc[z] = merge(rc[x], rc[y]);
    return z;
}

int ask(int x, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(!x) return 0;
    if(ql <= l && r <= qr) return 1;
    else if(qr <= mid) return ask(lc[x], l, mid, ql, qr);
    else if(ql >= mid + 1) return ask(rc[x], mid + 1, r, ql, qr);
    else return ask(lc[x], l, mid, ql, mid) || ask(rc[x], mid + 1, r, mid + 1, qr);
}

void init() {
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a'), modify(rt[last], 1, n, i);
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i > 1 ; -- i) {
        int u = bak[i], fa = pre[u];
        rt[fa] = merge(rt[fa], rt[u]);
    }
}

void sol(int l, int r) {
    int strm = strlen(s + 1), lim = strm;
    for(int i = 1, u = 1 ; i <= strm ; ++ i) {
        int c = s[i] - 'a';
        if(ch[u][c]) {
            u = ch[u][c];
            pos[i] = u;
        } else {
            lim = i - 1;
            break;
        }
    }
    pos[0] = 1;
    for(int i = lim ; i >= 0 ; -- i) {
        for(int j = (i < strm ? s[i + 1] - 'a' + 1 : 0) ; j < 26 ; ++ j) {
            if(ask(rt[ch[pos[i]][j]], 1, n, l + i, r)) {
                for(int k = 1 ; k <= i ; ++ k) {
                    putchar(s[k]);
                }
                putchar(j + 'a');
                puts("");
                return ;
            }
        }
    }
    puts("-1");
}

int main() {
    scanf("%s%d", s + 1, &m);
    init();
    for(int i = 1, l, r ; i <= m ; ++ i) {
        scanf("%d%d%s", &l, &r, s + 1);
        sol(l, r);
    }
}
