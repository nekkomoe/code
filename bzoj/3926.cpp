// 题意：给定20个字符串，求本质不同的子串个数
// 题解：在trie树上以父亲节点的sam为基础建立当前节点的sam
// 标签：后缀树, 后缀数组, 后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 4000005;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int w[N], n, c, d[N];

int len[N], ch[N][11], pre[N], cnt = 1;

int nd(int l) { return len[++ cnt] = l, cnt; }

int ins(int v, int p) {
    int np, q, nq;
    np = nd(len[p] + 1);
    pre[np] = 1;
    while(p && !ch[p][v]) ch[p][v] = np, p = pre[p];
    if(!p) return np;
    q = pre[np] = ch[p][v];
    if(len[p] + 1 != len[q]) {
        nq = nd(len[p] + 1);
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        pre[nq] = pre[q], pre[q] = pre[np] = nq;
        while(p && ch[p][v] == q) ch[p][v] = nq, p = pre[p];
    }
    return np;
}

void dfs(int u, int fa, int p) {
    int now = ins(w[u], p);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u, now);
    }
}

int main() {
    scanf("%d%d", &n, &c);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &w[i]);
    for(int i = 1 ; i < n ; ++ i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u), ++ d[u], ++ d[v];
    }
    for(int i = 1 ; i <= n ; ++ i) if(d[i] == 1) dfs(i, 0, 1);
    long long ans = 0;
    for(int i = 1 ; i <= cnt ; ++ i) ans += len[i] - len[pre[i]];
    printf("%lld\n", ans);
}
