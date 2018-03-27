#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <ctime>
#include <cctype>
#include <cfloat>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <bitset>
 
using namespace std;
 
#ifdef ONLINE_JUDGE
    #define debug
    #define log(message)
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
    #define log(message) puts(message)
#endif
 
#define INF 0x3f3f3f3f
 
#define INFLL 0x3f3f3f3f3f3f3f3fLL
 
void closeSync() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
 
template<class T> void read(T &x) {
    x = 0; int f = 0; char ch = getchar();
    while(ch < '0' || ch > '9') f |= (ch == '-'), ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
    x = f ? -x : x;
}
 
typedef long long ll;
 
// to do
 
const int N = 410000;
 
int n, m;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int sz[N], son[N], top[N], fa[N], l[N], r[N], deep[N], cnt;
 
void dfs(int u) {
    u[sz] = 1;
    u[deep] = u[fa][deep] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa]) {
            v[fa] = u;
            dfs(v);
            u[sz] += v[sz];
            if(u[son][sz] < v[sz]) {
                u[son] = v;
            }
        }
    }
}
 
void dfs(int u, int tp) {
    u[l] = ++ cnt;
    u[top] = tp;
    if(u[son]) dfs(u[son], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa] && v != u[son]) {
            dfs(v, v);
        }
    }
    u[r] = cnt;
}
 
ll tag[N * 10], mn[N * 10], ava[N * 10];
 
#define lc (id << 1)
 
#define rc (id << 1 | 1)
 
void build(int id, int l, int r) {
    ava[id] = 1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
 
void push(int id) {
    if(id[tag]) {
        id[mn] = id[tag];
        lc[tag] = id[tag];
        rc[tag] = id[tag];
        id[tag] = 0;
    }
}
 
void update(int id) {
    push(id), push(lc), push(rc);
    if(lc[ava] && rc[ava]) {
        id[mn] = min(lc[mn], rc[mn]);
    } else if(lc[ava]) {
        id[mn] = lc[mn];
    } else if(rc[ava]) {
        id[mn] = rc[mn];
    } else {
        id[mn] = INFLL;
    }
}
 
void modify(int id, int l, int r, int ql, int qr, ll v) {
    int mid = (l + r) >> 1;
    push(id);
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) id[tag] = v;
    else {
        modify(lc, l, mid, ql, qr, v);
        modify(rc, mid + 1, r, ql, qr, v);
        update(id);
    }
}
 
ll query(int id, int l, int r, int ql, int qr) {
    int mid = (l + r) >> 1;
    push(id);
    if(l > qr || r < ql) return INFLL;
    if(ql <= l && r <= qr) return id[mn];
    else return min(query(lc, l, mid, ql, qr), query(rc, mid + 1, r, ql, qr));
}
 
int root;
 
void modify(int u, int v, ll val) {
    while(u[top] != v[top]) {
        if(u[top][deep] < v[top][deep]) swap(u, v);
        modify(1, 1, n, u[top][l], u[l], val);
        u = u[top][fa];
    }
    if(u[deep] > v[deep]) swap(u, v);
    modify(1, 1, n, u[l], v[l], val);
}
 
int getlca(int u, int v) {
    while(u[top] != v[top]) {
        if(u[top][deep] < v[top][deep]) swap(u, v);
        u = u[top][fa];
    }
    return u[deep] < v[deep] ? u : v;
}
 
int get(int u, int rt) {
    while(rt[top] != u[top]) {
        if(rt[top][fa] == u) return rt[top];
        rt = rt[top][fa];
    }
    return u[son];
}
 
ll query(int u) {
    int lca = getlca(u, root);
    if(root == u) {
        return query(1, 1, n, 1, n);
    } else if(lca != u) {
        return query(1, 1, n, u[l], u[r]);
    } else {
        int v = get(u, root);
        return min(query(1, 1, n, 1, v[l] - 1), query(1, 1, n, v[r] + 1, n));
    }
}
 
ll val[N];
 
int main() {
    memset(mn, 0x3f, sizeof(mn));
    read(n), read(m);
    build(1, 1, n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        read(u), read(v);
        add(u, v);
        add(v, u);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        read(val[i]);
    }
    read(root);
    dfs(root);
    dfs(root, root);
    for(int i = 1 ; i <= n ; ++ i) {
        modify(1, 1, n, i[l], i[l], i[val]);
    }
    for(int i = 1, op, u, p1, p2, v ; i <= m ; ++ i) {
        read(op);
        if(op == 1) {
            read(root);
        } else if(op == 2) {
            read(p1), read(p2), read(v);
            modify(p1, p2, v);
        } else {
            read(u);
            printf("%lld\n", query(u));
        }
    }
    return 0;
}
