#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, m;

int ch[N][2], sum[N], val[N], rev[N], fa[N];

void update(int x) {
    sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]];
}

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = ch[y][1] == x;
    if(!isroot(y)) ch[z][ch[z][1] == y] = x;
    fa[x] = z;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
    update(y), update(x);
}

void push(int x) {
    if(rev[x]) {
        rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
        swap(ch[x][0], ch[x][1]);
        rev[x] = 0;
    }
}

void cha(int x) {
    if(!isroot(x)) cha(fa[x]);
    push(x);
}

void splay(int x) {
    cha(x);
    for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x]) {
        if(!isroot(y)) {
            rot(((ch[fa[y]][1] == y) == (ch[y][1] == x)) ? y : x);
        }
    }
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x]) {
        splay(x);
        ch[x][1] = y;
        update(x);
    }
}

void makeroot(int x) {
    access(x), splay(x), rev[x] ^= 1;
}

void link(int u, int v) {
    makeroot(u), access(v), splay(u);
    if(ch[u][1] != v) fa[u] = v;
}

void cut(int u, int v) {
    makeroot(u), access(v), splay(u);
    if(ch[u][1] == v) ch[u][1] = 0, fa[v] = 0, update(u);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &val[i]), sum[i] = val[i];
    for(int i = 1, op, x, y ; i <= m ; ++ i) {
        scanf("%d%d%d", &op, &x, &y);
        if(op == 0) {
            makeroot(x), access(y), splay(x);
            printf("%d\n", sum[x]);
        } else if(op == 1) {
            link(x, y);
        } else if(op == 2) {
            cut(x, y);
        } else {
            makeroot(x), splay(x), val[x] = y, update(x);
        }
    }
}

