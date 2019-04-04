#include "bits/stdc++.h"
using namespace std;
const int N = 2e6 + 10;
typedef long long ll;
char str[N];
int n;

int lc[36000010], rc[36000010], tot, root[N], mxn;

void modify(int &x, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    if(!x) x = ++ tot;
    if(l == r) {
        return ;
    } else if(pos <= mid) {
        modify(lc[x], l, mid, pos);
    } else {
        modify(rc[x], mid + 1, r, pos);
    }
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    int z = ++ tot;
    lc[z] = merge(lc[x], lc[y]);
    rc[z] = merge(rc[x], rc[y]);
    return z;
}

int ask(int x, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    if(!x || ql > r || qr < l) return 0;
    else if(ql <= l && r <= qr) return 1;
    else return ask(lc[x], l, mid, ql, qr) || ask(rc[x], mid + 1, r, ql, qr);
}

struct SAM {
    int p, q, np, nq, last, cnt;
    int ch[N][26], pre[N], len[N], tmp[N], bak[N], pos[N], R[N];

    SAM() {
        last = cnt = 1;    
    }

    void clear() {
        for(int i = 0 ; i <= cnt ; ++ i) {
            memset(ch[i], 0, sizeof ch[i]);
            pre[i] = len[i] = tmp[i] = bak[i] = pos[i] = R[i] = 0;
        }
        last = cnt = 1;
    }

    int nd(int l) { return len[++ cnt] = l, cnt; }

    void ins(int c, int id) {
        pre[last = np = nd(len[p = last] + 1)] = 1;
        pos[id] = np;
        R[np] = id;
        while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
        if(p) {
            pre[np] = q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
                R[nq] = R[q];
                for(int j = 0 ; j < 26 ; ++ j) {
                    ch[nq][j] = ch[q][j];
                }
                while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            }
        }
    }

    void get_right(int t) {
        for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
        for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
        for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
        if(!t) {
            for(int i = cnt ; i ; -- i) {
                if(pre[bak[i]]) {
                    root[pre[bak[i]]] = merge(root[pre[bak[i]]], root[bak[i]]);
                }
            }
        }
    }
} sam_str, sam;

void init_str() {
    scanf("%s", str + 1);
    mxn = strlen(str + 1);
    for(int i = 1 ; i <= mxn ; ++ i) {
        sam_str.ins(str[i] - 'a', i);
        modify(root[sam_str.pos[i]], 1, mxn, i);
    }
    sam_str.get_right(0);
}

int mx[N];

void runprog() {
    int l, r;
    scanf("%s%d%d", str + 1, &l, &r);
    n = strlen(str + 1);
    sam.clear();
    for(int i = 1 ; i <= n ; ++ i) {
        sam.ins(str[i] - 'a', i);
    }
    for(int i = 1, u = 1, cnt = 0 ; i <= n ; ++ i) {
        int c = str[i] - 'a';
        while(1) {
            if(!ask(root[sam_str.ch[u][c]], 1, mxn, l + cnt, r)) {
                if(!cnt) {
                    break;
                }
                -- cnt;
                if(cnt == sam_str.len[sam_str.pre[u]]) {
                    u = sam_str.pre[u];
                }
            } else {
                ++ cnt;
                u = sam_str.ch[u][c];
                break;
            }
        }
        mx[i] = cnt;
    }

    sam.get_right(1);
    ll ans = 0;
    for(int u = 2 ; u <= sam.cnt ; ++ u) {
        ans += max(sam.len[u] - max(sam.len[sam.pre[u]], mx[sam.R[u]]), 0);
    }
    printf("%lld\n", ans);
}

int main() {
    init_str();
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
