#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
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
 
inline int read() {
    static int f,ret;
    static char c;
    ret = 0, f = 1;
    c = getchar();
    while(c > '9' || c < '0'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') ret = (ret << 1) + (ret << 3) + c - '0', c = getchar();
    return f == 1 ? ret : -ret;
}
 
typedef long long ll;
 
// to do
 
const int N = 200010;
 
int head[N], to[N], rest[N];
 
void add(int u, int v) {
    static int tot = 0;
    ++ tot,
    to[tot] = v,
    rest[tot] = head[u],
    head[u] = tot;
}
 
int n, q;
 
int sz[N], son[N], fa[N], top[N], deep[N], l[N], r[N];
 
void dfs(int u) {
    u[deep] = u[fa][deep] + 1,
    u[sz] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa]) {
            v[fa] = u,
            dfs(v),
            u[sz] += v[sz];
            if(u[son][sz] < v[sz]) u[son] = v;
        }
    }
}
 
void dfs(int u, int tp) {
    static int tot = 0;
    u[top] = tp,
    u[l] = ++ tot;
    if(u[son]) dfs(u[son], tp);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[son] && v != u[fa]) dfs(v, v);
    }
    u[r] = tot;
}
 
int sum[N * 4], tag[N * 4];
 
#define lc (id << 1)
 
#define rc (id << 1 | 1)
 
void push(int id, int l, int r) {
    if(id[tag] != -1)
        lc[tag] = id[tag],
        rc[tag] = id[tag],
        id[sum] = id[tag] * (r - l + 1),
        id[tag] = -1;
}
 
void update(int id, int l, int r) {
    int mid = (l + r) >> 1;
    push(id, l, r), push(lc, l, mid), push(rc, mid + 1, r),
    id[sum] = lc[sum] + rc[sum];
}
 
void modify(int id, int l, int r, int ql, int qr, int v) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(ql == l && r == qr)
        id[tag] = v;
    else if(qr <= mid)
        modify(lc, l, mid, ql, qr, v),
        update(id, l, r);
    else if(ql >= mid + 1)
        modify(rc, mid + 1, r, ql, qr, v),
        update(id, l, r);
    else
        modify(lc, l, mid, ql, mid, v),
        modify(rc, mid + 1, r, mid + 1, qr, v),
        update(id, l, r);
}
 
int query(int id, int l, int r, int ql, int qr) {
    push(id, l, r);
    int mid = (l + r) >> 1;
    if(ql == l && r == qr) return id[sum];
    else if(qr <= mid)
        return query(lc, l, mid, ql, qr);
    else if(ql >= mid + 1)
        return query(rc, mid + 1, r, ql, qr);
    else
        return query(lc, l, mid, ql, mid) + query(rc, mid + 1, r, mid + 1, qr);
}
 
int main() {
    // freopen("in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1, x ; i < n ; ++ i)
        scanf("%d", &x),
        add(x + 1, i + 1);
    dfs(1);
    dfs(1, 1);
    memset(tag, -1, sizeof(tag));
    scanf("%d", &q);
    for(int i = 1, x ; i <= q ; ++ i) {
        char op[15];
        scanf("%s%d", op, &x), ++ x;
        if(op[0] == 'i') {
            // install
            if(query(1, 1, n, x[l], x[l]))
                puts("0");
            else {
                int ans = x[deep];
                while(x[top] != 1[top])
                    ans -= query(1, 1, n, x[top][l], x[l]),
                    modify(1, 1, n, x[top][l], x[l], 1),
                    x = x[top][fa];
                ans -= query(1, 1, n, 1[l], x[l]);
                modify(1, 1, n, 1[l], x[l], 1);
                printf("%d\n", ans);
            }
        } else {
            // uninstall
            if(query(1, 1, n, x[l], x[l]))
                printf("%d\n", query(1, 1, n, x[l], x[r])),
                modify(1, 1, n, x[l], x[r], 0);
            else
                puts("0");
        }
    }
    return 0;
}
