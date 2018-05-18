#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5 + 10;
 
int n, m;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) { to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }
 
int dfn[N], fa[N][30], clk, deep[N], endpos[N];
 
void dfs(int u) {
    dfn[u] = ++ clk;
    deep[u] = deep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 25 ; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u][0]) fa[v][0] = u, dfs(v);
    }
    endpos[u] = clk;
}
 
int getlca(int u, int v) {
    if(deep[u] < deep[v]) swap(u, v);
    for(int i = 25 ; ~ i ; -- i) if(deep[fa[u][i]] >= deep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 25 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return u;
}
 
// 不确定对不对
int getson(int u, int len) {
    for(int i = 25 ; ~ i ; -- i) if((1 << i) <= len) len -= 1 << i, u = fa[u][i];
    return u;
}
 
struct BT {
    int a[N];
    void modify(int i, int v) { for( ; i <= n ; i += i & -i) a[i] += v; }
    int query(int i) { int r = 0; for( ; i ; i -= i & -i) r += a[i]; return r; }
} bt;
 
struct P {
    int x, y;
    int op; // 0: 添加  1: 查询（正贡献） -1: 查询（负贡献）
    int t;  // op=0: 1添加 -1删除   op!=0: 答案的id
} p[N * 5], q[N * 5];
 
int ans[N], ans_cnt, cnt;
 
void cdq(int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) return ;
    cdq(l, mid), cdq(mid + 1, r);
    for(int i = l, j = mid + 1, k = l ; k <= r ; ) {
        if(j > r || (i <= mid && p[i].x <= p[j].x)) { if(p[i].op == 0) bt.modify(p[i].y, p[i].t); q[k ++] = p[i ++]; }
        else { if(p[j].op) ans[p[j].t] += bt.query(p[j].y) * p[j].op; q[k ++] = p[j ++]; }
    }
    for(int i = l ; i <= mid ; ++ i) if(p[i].op == 0) bt.modify(p[i].y, -p[i].t); // 删除贡献
    for(int i = l ; i <= r ; ++ i) p[i] = q[i];
}
 
void add(int a, int b, int c, int d = ans_cnt) { p[++ cnt] = (P) { a, b, c, d }; }
 
int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs(1);
    scanf("%d", &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        p[++ cnt] = (P) { dfn[u], dfn[v], 0, 1 };
        p[++ cnt] = (P) { dfn[v], dfn[u], 0, 1 };
    }
    int q; scanf("%d", &q);
    for(int i = 1, op, u, v ; i <= q ; ++ i) {
        scanf("%d%d%d", &op, &u, &v);
        if(op == 1) add(dfn[u], dfn[v], 0, 1), add(dfn[v], dfn[u], 0, 1);
        else if(op == 2) add(dfn[u], dfn[v], 0, -1), add(dfn[v], dfn[u], 0, -1);
        else {
            ++ ans_cnt; if(deep[u] < deep[v]) swap(u, v);
            int son = getson(u, deep[u] - deep[v] - 1);
            if(deep[u] > deep[v] && fa[son][0] == v) add(dfn[u] - 1, dfn[son] - 1, -1), add(dfn[u] - 1, endpos[son], 1), add(dfn[u] - 1, n, -1), add(endpos[u], dfn[son] - 1, 1), add(endpos[u], endpos[son], -1), add(endpos[u], n, 1); // u和v在一条链上
            else add(dfn[u] - 1, dfn[v] - 1, 1), add(dfn[u] - 1, endpos[v], -1), add(endpos[u], dfn[v] - 1, -1), add(endpos[u], endpos[v], 1);
        }
    }
    cdq(1, cnt);
    for(int i = 1 ; i <= ans_cnt ; ++ i) printf("%d\n", ans[i]);
}
