%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize(4)
%:pragma GCC optimize(5)
%:pragma GCC optimize(6)
%:pragma GCC optimize(7)
%:pragma GCC optimize(8)
%:pragma GCC optimize(9)

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(4)
#pragma GCC optimize(5)
#pragma GCC optimize(6)
#pragma GCC optimize(7)
#pragma GCC optimize(8)
#pragma GCC optimize(9)

#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e6 + 10;

int n, q, a, b, ans;

int len[N], pre[N], ch[N][30], tot = 1, last = 1;

// lct

int w[N], son[N][2], fa[N], tag[N];

int isroot(int u) { return son[fa[(u)]][0] != (u) && son[fa[(u)]][1] != (u); }

inline int setit(int x, int y) { w[(x)] += (y), tag[(x)] += (y); }

inline int push(int u) { tag[(u)] && setit(son[(u)][0], tag[(u)]), setit(son[(u)][1], tag[(u)]), tag[(u)] = 0; }

void rot(int x) {
    int y = fa[x], z = fa[y], k = son[y][1] == x;
    if(!isroot(y)) son[z][son[z][1] == y] = x;
    fa[x] = z;
    fa[son[y][k] = son[x][k ^ 1]] = y;
    fa[son[x][k ^ 1] = y] = x;
}

int sta[N], tp;

void splay(int x) {
    sta[tp = 1] = x;
    for(int i = x ; !isroot(i) ; i = fa[i]) sta[++ tp] = fa[i];
    while(tp) push(sta[tp --]);
    for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x])
        if(!isroot(y))
            rot((son[y][1] == x) == (son[fa[y]][1] == y) ? y : x);
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x])
        splay(x), son[x][1] = y;
}

#define link(u, v) (fa[(v)] = (u), access((u)), splay((u)), setit((u), w[(v)]))

#define cut(u) (access((u)), splay((u)), setit(son[(u)][0], -w[(u)]), fa[son[(u)][0]] = 0, son[(u)][0] = 0)

// sam

void ins(int c) {

    int p, np, q, nq;
    p = last;
    pre[len[np = last = ++ tot] = len[p] + 1, tot] = 1;
    w[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {

            len[nq = ++ tot] = len[p] + 1;

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

void write(int x) {
    if(x / 10) write(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    scanf("%s", s + 1);
    for(int i = 1 ; s[i] ; ++ i) ins(s[i] - 'a' + 1);

    scanf("%d%d%d", &q, &a, &b);
    while(q --) {
        scanf("%s", s + 1);
        ans = 0;
        int p = 1;
        for(int i = 1 ; s[i] ; ++ i) {
            p = ch[p][s[i] - 'a' + 1];
            if(!p) goto nxt;
        }
        sta[tp = 1] = p;
        for(int i = p ; !isroot(i) ; i = fa[i]) sta[++ tp] = fa[i];
        while(tp) push(sta[tp --]);
        ans = w[p];
        nxt: write(ans), putchar('\n');
        ins((a * ans + b) % 26 + 1);
    }
}
