// 题意：求出现至少k次的子串最长长度
// 题解：模型转化为后缀树上的节点子树中后缀节点个数不少于k个的最深的节点
// 标签：后缀树, 后缀数组, 后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 40010;

int ch[N][110], sz[N], pre[N], len[N], p, np, q, nq, last = 1, cnt = 1;

int nd(int l) { return len[++ cnt] = l, cnt; }

void ins(int v) {
    last = np = nd(len[p = last] + 1);
    pre[np] = sz[np] = 1;
    while(p && !ch[p][v]) ch[p][v] = np, p = pre[p];
    if(!p) return ;
    pre[np] = q = ch[p][v];
    if(len[p] + 1 != len[q]) {
        nq = nd(len[p] + 1);
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        pre[nq] = pre[q], pre[q] = pre[np] = nq;
        while(p && ch[p][v] == q) ch[p][v] = nq, p = pre[p];
    }
}

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int n, k, a[N], ans;

void dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        dfs(v);
        sz[u] += sz[v];
    }
    if(u == 1) return ;
    if(sz[u] >= k) ans = max(ans, len[u]);
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = n ; i >= 1 ; -- i) ins(a[i]);
    for(int i = 2 ; i <= cnt ; ++ i) add(pre[i], i);
    dfs(1);
    printf("%d\n", ans);
}
