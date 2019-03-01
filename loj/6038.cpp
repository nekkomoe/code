#include "bits/stdc++.h"
typedef long long ll;
using namespace std;
const int N = 5e5 + 10;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int n, q, lastans;

int acc[N]; int get(int x) { return x == acc[x] ? x : acc[x] = get(acc[x]); }

struct T {
    int x, y, dis;
} neko[N];
bool operator < (T a, T b) {
    return a.dis < b.dis;
}

int ch[N][2], sum[N], rev[N], fa[N];

void update(int x) {
    sum[x] = sum[ch[x][0]] + 1 + sum[ch[x][1]];
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

int getdis(int u, int v) {
    makeroot(u), access(v), splay(v);
    return sum[v] - 1;
}

void tolink(int u, int v) {

    assert(get(u) != get(v));

    T tu = neko[get(u)], tv = neko[get(v)];
    acc[get(u)] = get(v);
    link(u, v);
    T res = (T) { -1, -1, -1 };

    vector<int> pts;
    pts.push_back(tu.x), pts.push_back(tu.y);
    pts.push_back(tv.x), pts.push_back(tv.y);

    for(int x: pts) {
        for(int y: pts) {
            res = max(res, (T) { x, y, getdis(x, y) });
        }
    }

    neko[get(v)] = res;
}

int main() {
    int type = io(), n = io(), q = io();
    for(int i = 1 ; i <= n ; ++ i) {
        acc[i] = i;
        sum[i] = 1;
        neko[i] = (T) { i, i, 0 };
    }
    while(q --) {
        int op = io(), u = io() ^ lastans;
        if(op == 1) {
            int v = io() ^ lastans;
            // printf("u = %d, v = %d\n", u, v);
            tolink(u, v);
        } else {
            // printf("u = %d\n", u);
            lastans = max(getdis(u, neko[get(u)].x), getdis(u, neko[get(u)].y));
            io(lastans);
        }

        if(type == 0) {
            lastans = 0;
        }
    }
}
