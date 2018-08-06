#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

char s[N];

map<int, int> ch[N];

int pre[N], len[N], sz[N], last = 1, cnt = 1, n, m, ans, vis[N], a[N], t, head[N], rest[N], to[N], tot, dfn[N], ddd, sta[N], fa[N][30], deep[N];

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

int pos[N];

void ins(int c, int i) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    pos[i] = np;
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q];
            pre[q] = pre[np] = nq;
            ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
    dfn[u] = ++ ddd, deep[u] = deep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 25 ; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        fa[v][0] = u;
        dfs(v);
    }
}

int getlca(int u, int v) {
    if(deep[u] < deep[v]) swap(u, v);
    for(int i = 25 ; ~ i ; -- i) if(deep[fa[u][i]] >= deep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 25 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

void dp(int u, int fa) {
    sz[u] = vis[u] == m + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        dp(v, u);
        sz[u] += sz[v];
    }
    ans += sz[u] * (sz[u] - 1) * (len[u] - len[fa]) / 2;
    head[u] = 0;
}

int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    for(int i = n ; i ; -- i) ins(s[i], i);
    for(int i = 1 ; i <= cnt ; ++ i) add(pre[i], i);
    dfs(1), memset(head, 0, sizeof head);
    while(m --) {
        scanf("%d", &t);
        for(int i = 1 ; i <= t ; ++ i) scanf("%d", &a[i]);
        sort(a + 1, a + 1 + t);
        t = unique(a + 1, a + 1 + t) - a - 1;
        for(int i = 1 ; i <= t ; ++ i) a[i] = pos[a[i]];
        sort(a + 1, a + 1 + t, cmp);
        int p = tot = 0;
        for(int i = 1, u, lca ; i <= t ; ++ i) {
            vis[u = a[i]] = m + 1;
            if(p) {
                lca = getlca(u, sta[p]);
                while(dfn[lca] < dfn[sta[p]]) {
                    if(dfn[lca] >= dfn[sta[p - 1]]) {
                        add(lca, sta[p --]);
                        if(lca != sta[p]) sta[++ p] = lca;
                        break;
                    }
                    add(sta[p - 1], sta[p]), -- p;
                }
            }
            sta[++ p] = u;
        }
        while(p > 1) add(sta[p - 1], sta[p]), -- p;
        dp(sta[1], ans = 0);
        printf("%d\n", ans);
    }
}
