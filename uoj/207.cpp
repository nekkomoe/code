#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace OINAMP {

    const int N = 2e6 + 10;

    ll ops[N][3]; // (x,y,d)

    int ch[N][2], fa[N], rev[N];
    ll sum[N], val[N], sumlight[N];

    void upd(int x) {
        sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x] ^ sumlight[x];
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

    void dfspush(int x) {
        if(!isroot(x)) {
            dfspush(fa[x]);
        }
        push(x);
    }

    int isrig(int x) {
        return ch[fa[x]][1] == x;
    }
    void rot(int x) {
        int y = fa[x], z = fa[y];
        int k = isrig(x);
        fa[x] = z;
        fa[ch[y][k] = ch[x][!k]] = y;
        upd(y);
        fa[ch[x][!k] = y] = x;
        upd(x);
        if(ch[z][0] == y) {
            ch[z][0] = x;
        }
        if(ch[z][1] == y) {
            ch[z][1] = x;
        }
    }

    void splay(int x) {
        dfspush(x);
        for(int y = fa[x] ; !isroot(x) ; rot(x), y = fa[x]) {
            if(!isroot(y)) {
                rot(isrig(x) == isrig(y) ? y : x);
            }
        }
    }

    void access(int x) {
        for(int y = 0 ; x ; y = x, x = fa[x]) {
            splay(x);
            sumlight[x] ^= sum[ch[x][1]];
            ch[x][1] = y;
            sumlight[x] ^= sum[ch[x][1]];
            upd(x);
        }
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }

    void link(int x, int y) {
        makeroot(x), makeroot(y);
        fa[x] = y;
        sumlight[y] ^= sum[x];
        upd(y);
    }
    void cut(int x, int y) {
        makeroot(y);
        access(x);
        splay(x);
        fa[y] = ch[x][0] = 0;
        upd(x);
    }
    void modify(int x, ll d) {
        access(x), splay(x);
        val[x] ^= d;
        upd(x);
    }

    ll xorsum;

    int ask(int x, int y) {
        makeroot(x), access(y);
        return (val[y] ^ sumlight[y]) == xorsum;
    }

    void main() {
        int n, m;
        scanf("%*d%d%d", &n, &m);
        for(int i = 1, u, v ; i < n ; ++ i) {
            scanf("%d%d", &u, &v);
            link(u, v);
        }
        int idsops = 0;
        while(m --) {
            int ty; scanf("%d", &ty);
            if(ty == 1) {
                int x, y, u, v; scanf("%d%d%d%d", &x, &y, &u, &v);
                cut(x, y);
                link(u, v);
            } else if(ty == 2) {
                int x, y; scanf("%d%d", &x, &y);
                idsops ++;
                ll val = ops[idsops][0] = (ll) rand() * rand();
                ops[idsops][1] = x;
                ops[idsops][2] = y;
                modify(x, val);
                modify(y, val);
                xorsum ^= val;
            } else if(ty == 3) {
                int ids; scanf("%d", &ids);
                modify(ops[ids][1], ops[ids][0]);
                modify(ops[ids][2], ops[ids][0]);
                xorsum ^= ops[ids][0];
            } else {
                int x, y; scanf("%d%d", &x, &y);
                puts(ask(x, y) ? "YES" : "NO");
            }
        }
    }
}

int main() {
    OINAMP :: main();
}
