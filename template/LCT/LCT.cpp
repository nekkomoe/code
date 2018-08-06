// https://www.luogu.org/problemnew/show/P3690 

#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, m;

int fa[N], ch[N][2], sum[N], val[N], rev[N], s[N], p;

inline void read(int &x) {
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

void update(int x) {
    sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]];
}

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void push(int x) {
    if(rev[x]) {
        swap(ch[x][0], ch[x][1]);
        rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
        rev[x] = 0;
    }
}

void rot(int x) {
    int y = fa[x], z = fa[y], l = ch[y][1] == x, r = !l;
    if(!isroot(y)) ch[z][ch[z][1] == y] = x;
    fa[ch[y][l] = ch[x][r]] = y;
    fa[ch[x][r] = y] = x;
    fa[x] = z;
    update(y), update(x);
}

void splay(int x) {
    s[p = 1] = x;
    for(int i = x ; !isroot(i) ; i = fa[i]) s[++ p] = fa[i];
    while(p) push(s[p --]);
    for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x]) 
        if(!isroot(y))
            rot((ch[y][1] == x) == (ch[fa[y]][1] == y) ? y : x);
}

void vis(int x) {
    int t = 0;
    while(x) {
        splay(x);
        ch[x][1] = t, update(x);
        t = x, x = fa[x];
    }
}

void makeroot(int x) {
    vis(x), splay(x), rev[x] ^= 1;
}

void cut(int x, int y) {
    makeroot(x), vis(y), splay(x);
    if(ch[x][1] == y) ch[x][1] = fa[y] = 0, update(x);
}

void link(int x, int y) {
    makeroot(x), vis(y), splay(x);
    if(ch[x][1] != y) fa[x] = y;
}

int main() {
    read(n), read(m);
    for(int i = 1 ; i <= n ; ++ i) read(sum[i]), val[i] = sum[i];
    for(int i = 1, op, x, y ; i <= m ; ++ i) {
        read(op), read(x), read(y);
        if(op == 0) makeroot(x), vis(y), splay(x), printf("%d\n", sum[x]);
        else if(op == 1) link(x, y);
        else if(op == 2) cut(x, y);
        else makeroot(x), splay(x), val[x] = y, update(x);
    }
}
