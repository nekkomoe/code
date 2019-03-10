#include "bits/stdc++.h"
using namespace std;

const int N = 2e6 + 10;
int n;
#define lc ch[x][0]
#define rc ch[x][1]
int ch[N][2], n1[N], n2[N], val[N], tag[N], fa[N];

void push(int x, int ad) {
    val[x] ^= 3;
    swap(n1[x], n2[x]);
    tag[x] += ad;
}

void upd(int x) {
    if(!(n1[x] = n1[rc]) && !(n1[x] = x * (val[x] != 1))) {
        n1[x] = n1[lc];
    }
    if(!(n2[x] = n2[rc]) && !(n2[x] = x * (val[x] != 2))) {
        n2[x] = n2[lc];
    }
}

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void goupd(int x) {
    if(!isroot(x)) goupd(fa[x]);
    if(tag[x]) {
        push(lc, tag[x]);
        push(rc, tag[x]);
        tag[x] = 0;
    }
}

int isrig(int x) {
    return ch[fa[x]][1] == x;
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x), w = ch[x][!k];
    if(!isroot(y)) ch[z][isrig(y)] = x;
    fa[fa[fa[ch[ch[x][!k] = y][k] = w] = y] = x] = z, upd(y);
}

void splay(int x) {
    goupd(x);
    for( ; !isroot(x) ; rot(x))
        if(!isroot(fa[x]))
            rot(isrig(x) == isrig(fa[x]) ? fa[x] : x);
    upd(x);
}

void access(int x) {
    for(int y = 0 ; x ; x = fa[x]) {
        splay(x);
        rc = y;
        upd(y = x);
    }
}

int deg[N];

int main() {
    scanf("%d", &n);
    for(int i = 1, x, y, z ; i <= n ; ++ i) {
        scanf("%d%d%d", &x, &y, &z);
        fa[x] = fa[y] = fa[z] = i;
        deg[i] = 3;
    }
    queue<int> q;
    for(int i = n + 1 ; i <= 3 * n + 1 ; ++ i) {
        q.push(i);
        scanf("%d", &val[i]);
        val[i] <<= 1;
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        if(fa[u] && ! -- deg[fa[u]]) q.push(fa[u]);
        if(u <= n) upd(u);
        val[fa[u]] += val[u] >> 1;
    }
    int ans = val[1] >> 1;
    int Q; scanf("%d", &Q); while(Q --) {
        int x; scanf("%d", &x);
        int type = (val[x] ^= 2) - 1;
        access(x = fa[x]), splay(x);
        if((~ type ? n1 : n2)[x]) {
            splay(x = (~ type ? n1 : n2)[x]);
            push(rc, type), upd(rc);
            val[x] += type, upd(x);
        } else {
            push(x, type), upd(x), ans ^= 1;
        }
        printf("%d\n", ans);
    }
}
