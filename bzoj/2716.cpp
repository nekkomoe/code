%:pragma GCC optimize(2)

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int read() {
    int x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

int n, m, root;

struct P {
    int d[2], x[2], y[2], ch[2], fa, sz, act, id;
    void init(P p) { x[0] = x[1] = d[0] = p.d[0], y[0] = y[1] = d[1] = p.d[1];}
    int dis(P &p) {
        return max(x[0] - p.d[0], 0) + max(p.d[0] - x[1], 0) + max(y[0] - p.d[1], 0) + max(p.d[1] - y[1], 0);
    }
} p[N], a[N], la;

struct Q {
    int t, id, d[2];
} que[N];

void update(P &a) {
    a.x[0] = min(a.d[0], min(p[a.ch[0]].x[0], p[a.ch[1]].x[0]));
    a.x[1] = max(a.d[0], max(p[a.ch[0]].x[1], p[a.ch[1]].x[1]));
    a.y[0] = min(a.d[1], min(p[a.ch[0]].y[0], p[a.ch[1]].y[0]));
    a.y[1] = max(a.d[1], max(p[a.ch[0]].y[1], p[a.ch[1]].y[1]));
    a.sz = p[a.ch[0]].sz + a.act + p[a.ch[1]].sz;
}

int cnt;

int D;

bool operator < (const P &a, const P &b) {
    return a.d[D] < b.d[D];
}

int pos[N];

void build(int &o, int l, int r, int d) {
    if(l > r) return ;
    D = d;
    int mid = (l + r) >> 1;
    nth_element(a + l, a + mid, a + r + 1);
    pos[a[mid].id] = o = ++ cnt;
    p[o].init(a[mid]);
    p[o].act = a[mid].act;
    build(p[o].ch[0], l, mid - 1, d ^ 1);
    build(p[o].ch[1], mid + 1, r, d ^ 1);
    if(p[o].ch[0]) p[p[o].ch[0]].fa = o;
    if(p[o].ch[1]) p[p[o].ch[1]].fa = o;
    update(p[o]);
}

int ans;

inline int dis(P &a, P &b) {
    return abs(a.d[0] - b.d[0]) + abs(a.d[1] - b.d[1]);
}

void query(int u) {
    
    int d0 = 0x3f3f3f3f, d1 = d0;
    
    if(p[u].ch[0]) d0 = p[p[u].ch[0]].dis(la);
    if(p[u].ch[1]) d1 = p[p[u].ch[1]].dis(la);
    
    if(p[u].act) ans = min(ans, dis(p[u], la));
    
    if(d0 < d1) {
        if(d0 < ans && p[p[u].ch[0]].sz) query(p[u].ch[0]);
        if(d1 < ans && p[p[u].ch[1]].sz) query(p[u].ch[1]);
    } else {
        if(d1 < ans && p[p[u].ch[1]].sz) query(p[u].ch[1]);
        if(d0 < ans && p[p[u].ch[0]].sz) query(p[u].ch[0]);
    }
}

int main() {    
    p[0].x[0] = 0x3f3f3f3f, p[0].x[1] = 0xcfcfcfcf;
    p[0].y[0] = p[0].x[0], p[0].y[1] = p[0].x[1];
    n = read(), m = read();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i].d[0] = read(), a[i].d[1] = read(), a[i].act = 1, a[i].id = i;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        que[i].t = read(), que[i].d[0] = read(), que[i].d[1] = read();
        if(que[i].t == 1) {
            a[++ n].d[0] = que[i].d[0], a[n].d[1] = que[i].d[1], a[n].id = n;
            que[i].id = n;
        }
    }
    build(root, 1, n, 0);
    for(int i = 1 ; i <= m ; ++ i) {
        if(que[i].t == 1) {
            int u = pos[que[i].id];
            p[u].act = 1;
            while(u) {
                update(p[u]);
                u = p[u].fa;
            }
        } else {
            la.d[0] = que[i].d[0], la.d[1] = que[i].d[1];
            ans = 0x3f3f3f3f;
            query(root);
            printf("%d\n", ans);
        }
    }
}
