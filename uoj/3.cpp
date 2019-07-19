#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace NEKKO {

const int N = 2e6 + 10;

int ch[N][2], rev[N], val[N], info[N], fa[N];

void push(int x) {
    if(rev[x]) {
        swap(ch[x][0], ch[x][1]);
        rev[x] = 0;
        rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1;
    }
}

void upd(int x) {
    info[x] = x;
    if(val[info[ch[x][0]]] > val[info[x]]) {
        info[x] = info[ch[x][0]];
    }
    if(val[info[ch[x][1]]] > val[info[x]]) {
        info[x] = info[ch[x][1]];
    }
}

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

int isrig(int x) {
    return ch[fa[x]][1] == x;
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x);
    fa[x] = z;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
    upd(y), upd(x);
    if(ch[z][0] == y) {
        ch[z][0] = x;
    }
    if(ch[z][1] == y) {
        ch[z][1] = x;
    }
}

void dfs(int x) {
    if(!isroot(x)) {
        dfs(fa[x]);
    }
    push(x);
}

void splay(int x) {
    dfs(x);
    for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x]) {
        if(!isroot(y)) {
            rot(isrig(y) == isrig(x) ? y : x);
        }
    }
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x]) {
        splay(x);
        fa[ch[x][1] = y] = x;
        upd(x);
    }
}

void makeroot(int x) {
    access(x), splay(x);
    rev[x] ^= 1;
}

void link(int x, int y) {
    makeroot(x), makeroot(y);
    fa[x] = y;
}

void cut(int x, int y) {
    makeroot(x), access(y), splay(y);
    fa[x] = ch[y][0] = 0;
    upd(y);
}

int ask(int x, int y) {
    makeroot(x), access(y), splay(y);
    return info[y];
}

int dsu[N];
int getdsu(int x) {
    return x == dsu[x] ? x : dsu[x] = getdsu(dsu[x]);
}

int n, m;

struct OPS {
    int u, v, a, b;
} ops[N];
bool operator < (OPS x, OPS y) {
    return x.b < y.b;
}

void main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n + m ; ++ i) {
        dsu[i] = i;
        info[i] = i;
    }

    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d%d%d", &ops[i].u, &ops[i].v, &ops[i].a, &ops[i].b);
    }
    sort(ops + 1, ops + 1 + m);
    for(int i = 1 ; i <= m ; ++ i) {
        val[n + i] = ops[i].a;
    }
    ll ans = 0x3f3f3f3f3f3f3f3fll;
    for(int i = 1 ; i <= m ; ++ i) {
        ll coef = 0;
        int u = ops[i].u, v = ops[i].v, w = ops[i].a;

        int flag = 1; // 是否需要把这条边加上去

        if(getdsu(u) == getdsu(v)) {
            // 连通的话才尝试删边
            int z = ask(u, v);
            if(val[z] <= w) {
                // 并不需要删除
                flag = 0;
            } else {
                cut(z, ops[z - n].u), cut(z, ops[z - n].v);
            }
        } else {
            dsu[getdsu(u)] = getdsu(v);
        }
        if(flag) {
            link(n + i, u);
            link(n + i, v);
        }
        if(getdsu(1) == getdsu(n)) {
            // 如果1和n连通，才进行
            ans = min(ans, (ll) val[ask(1, n)] + ops[i].b);
        }
    }
    if(ans == 0x3f3f3f3f3f3f3f3fll) {
        puts("-1");
    } else {
        printf("%lld\n", ans);
    }
}

}

int main() {
    NEKKO :: main();
}
