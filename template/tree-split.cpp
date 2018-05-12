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

template<class T> inline void read(T &x) {
    x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ '0'), ch = getchar();
}

template<class T> inline void write(T x) {
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

typedef long long ll;

// to do

const int N = 200010;

int n, m, root, p;

int head[N], rest[N], to[N], tot;

inline void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}

int top[N], fa[N], deep[N], sz[N], lpos[N], rpos[N], son[N], cnt;

inline void dfs(int u) {
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

inline void dfs(int u, int tp) {
    u[lpos] = ++ cnt;
    u[top] = tp;
    if(u[son]) dfs(u[son], tp);
    for(int i = head[u], v ; i ; i = rest[i]) {
        v = to[i];
        if(v != u[fa] && v != u[son]) {
            dfs(v, v);
        }
    }
    u[rpos] = cnt;
}

ll tag[N * 30], sum[N * 30];

#define lc (id << 1)

#define rc (id << 1 | 1)

inline void push(int id, int l, int r) {
    if(id[tag]) {
        id[tag] %= p;
        lc[tag] += id[tag];
        rc[tag] += id[tag];
        (id[sum] += (r - l + 1) * id[tag]) %= p;
        id[tag] = 0;
    }
}

inline void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r); push(lc, l, mid); push(rc, mid + 1, r);
    (id[sum] = lc[sum] + rc[sum]) %= p;
}

inline void modify(int id, int l, int r, int ql, int qr, int v) {
    push(id, l, r);
    if(l > qr || r < ql) return;
    if(ql <= l && r <= qr) id[tag] += v;
    else {
        int mid = (l + r) >> 1;
        modify(lc, l, mid, ql, qr, v);
        modify(rc, mid + 1, r, ql, qr, v);
        update(id, l, r);
    }
}

inline int query(int id, int l, int r, int ql, int qr) {
    push(id, l, r);
    if(l > qr || r < ql) return 0;
    if(ql <= l && r <= qr) return id[sum] % p;
    else {
        int mid = (l + r) >> 1;
        return (query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr)) % p;
    }
}

inline void modify(int u, int v, int z) {
    while(u[top] != v[top]) {
        if(u[top][deep] < v[top][deep]) swap(u, v);
        modify(1, 1, n, u[top][lpos], u[lpos], z);
        u = u[top][fa];
    }
    if(u[deep] > v[deep]) swap(u, v);
    modify(1, 1, n, u[lpos], v[lpos], z);
}

inline int query(int u, int v) {
    int ret = 0;
    while(u[top] != v[top]) {
        if(u[top][deep] < v[top][deep]) swap(u, v);
        ret += query(1, 1, n, u[top][lpos], u[lpos]);
        ret %= p;
        u = u[top][fa];
    }
    if(u[deep] > v[deep]) swap(u, v);
    ret += query(1, 1, n, u[lpos], v[lpos]);
    return ret % p;
}

int x[N];

int main() {
    read(n); read(m); read(root); read(p);
    for(int i = 1 ; i <= n ; ++ i) {
        read(x[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        read(u); read(v);
        add(u, v);
        add(v, u);
    }
    dfs(root);
    dfs(root, root);
    for(int i = 1 ; i <= n ; ++ i) {
        modify(1, 1, n, i[lpos], i[lpos], x[i] % p);
    }
    for(int i = 1, op, x, y, z ; i <= m ; ++ i) {
        read(op); read(x);
        if(op == 1) {
            read(y); read(z);
            modify(x, y, z % p);
        } else if(op == 2) {
            read(y);
            write(query(x, y)); putchar('\n');
        } else if(op == 3) {
            read(z);
            modify(1, 1, n, x[lpos], x[rpos], z % p);
        } else {
            write(query(1, 1, n, x[lpos], x[rpos]) % p); putchar('\n');
        }
    }
}
