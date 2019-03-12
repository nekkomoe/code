
#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
 
int n, q, val[N];
 
int head[N], rest[N * 2], to[N * 2], tot;
 
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
struct Trie {
    int root[N], tot, ch[N * 35][2], cnt[N * 35];
    Trie() { root[0] = tot = 1; }
    void ins(int last, int &now, int x) {
        int rt = now = ++ tot;
        for(int i = 30 ; ~ i ; -- i) {
            int bit = (x >> i) & 1;
            ch[rt][!bit] = ch[last][!bit];
            ch[rt][bit] = ++ tot;
            rt = ch[rt][bit];
            last = ch[last][bit];
            cnt[rt] = cnt[last] + 1;
        }
    }
    int query(int L, int R, int x) {
        int res = 0;
        for(int i = 30 ; ~ i ; -- i) {
            int bit = (x >> i) & 1;
            if(cnt[ch[R][!bit]] - cnt[ch[L][!bit]]) {
                R = ch[R][!bit];
                L = ch[L][!bit];
                res |= 1 << i;
            } else {
                R = ch[R][bit];
                L = ch[L][bit];
            }
        }
        return res;
    }
} seq, tre;
 
int dfn[N], l[N], r[N], clk, fa[N][30], dep[N];
 
void dfs(int u, int fa) {
    tre.ins(tre.root[fa], tre.root[u], val[u]);
    :: fa[u][0] = fa;
    dep[u] = dep[fa] + 1;
    l[u] = ++ clk;
    dfn[clk] = val[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
    }
    r[u] = clk;
}
 
int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 25 ; ~ i ; -- i)
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if(u == v) return u;
    for(int i = 25 ; ~ i ; -- i)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i],
            v = fa[v][i];
    return fa[u][0];
}
 
int main() {
 
    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &val[i]);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    for(int j = 1 ; j <= 25 ; ++ j)
        for(int i = 1 ; i <= n ; ++ i)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    for(int i = 1 ; i <= n ; ++ i) {
        seq.ins(seq.root[i - 1], seq.root[i], dfn[i]);
    }
    for(int i = 1, op, x, y, z ; i <= q ; ++ i) {
        scanf("%d%d%d", &op, &x, &y);
        if(op == 1) {
            printf("%d\n", seq.query(seq.root[l[x] - 1], seq.root[r[x]], y));
        } else {
            scanf("%d", &z);
            int d = lca(x, y);
            printf("%d\n", max(tre.query(tre.root[fa[d][0]], tre.root[x], z), tre.query(tre.root[fa[d][0]], tre.root[y], z)));
        }
    }
}
