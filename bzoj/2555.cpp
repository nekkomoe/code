#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 2e6 + 10;

int n, q, a, b, ans;

int len[N], pre[N], ch[N][30], tot = 1, last = 1;

// lct

int w[N], son[N][2], fa[N], tag[N];

int isroot(int u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

void setit(int x, int y) {
    w[x] += y, tag[x] += y;
}

void push(int u) {
    if(tag[u]) {
        setit(son[u][0], tag[u]), setit(son[u][1], tag[u]);
        tag[u] = 0;
    }
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = son[y][1] == x;
    if(!isroot(y)) son[z][son[z][1] == y] = x;
    fa[x] = z;
    fa[son[y][k] = son[x][k ^ 1]] = y;
    fa[son[x][k ^ 1] = y] = x;
}

void pall(int u) {
    if(!isroot(u)) pall(fa[u]);
    push(u);
}

void splay(int x) {
    pall(x);
    for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x])
        if(!isroot(y))
            rot((son[y][1] == x) == (son[fa[y]][1] == y) ? y : x);
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x])
        splay(x), son[x][1] = y;
}

void link(int u, int v) {
    fa[v] = u;
    access(u), splay(u), setit(u, w[v]);
}

void cut(int u) {
    access(u), splay(u), setit(son[u][0], -w[u]);
    fa[son[u][0]] = 0, son[u][0] = 0;
}

// sam

int nd(int l) { return len[++ tot] = l, tot; }

void ins(int c) {

    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    w[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {

            nq = nd(len[p] + 1);

            cut(q), link(pre[q], nq);
            link(nq, np), link(nq, q);

            pre[nq] = pre[q], pre[np] = pre[q] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];

            return ;
        }
    }
    link(pre[np], np);
}

char s[N];

void dc(int mask) {
    for(int i = 0 ; s[i] ; ++ i) {
        mask = (mask * 131 + i) % n;
        swap(s[i], s[mask]);
    }
}

int main() {

    scanf("%d%s", &q, s);
    for(int i = 0 ; s[i] ; ++ i) {
        ins(s[i] - 'A');
    }

    int mask = 0;

    while(q --) {

        int tmp = mask;

        char op[10];
        scanf("%s%s", op, s);
        n = strlen(s);
        dc(mask);
        if(op[0] == 'A') for(int i = 0 ; s[i] ; ++ i) ins(s[i] - 'A');
        else {
            int ans = 0;
            int p = 1;
            for(int i = 0 ; s[i] ; ++ i) {
                int c = s[i] - 'A';
                if(ch[p][c]) p = ch[p][c];
                else goto nxt;
            }
            pall(p);
            ans = w[p];
            nxt: printf("%d\n", ans);
            mask ^= ans;
        }
    }
}
