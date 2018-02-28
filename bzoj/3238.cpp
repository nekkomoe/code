// 题意：求两两子串的lcp的和
// 题解：模型转化为后缀树上的节点是多少个后缀节点的lca
// 标签：后缀树, 后缀数组, 后缀自动机

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1500010;

ll ans;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int ch[N][30], sz[N], len[N], pre[N], cnt = 1, p, np, q, nq, last = 1;

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

void dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        dfs(to[i]);
        sz[u] += sz[to[i]];
    }
    if(u != 1) ans -= (ll) sz[u] * (sz[u] - 1) * (len[u] - len[pre[u]]);
}

char s[N];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for(int i = n ; i ; -- i) ins(s[i] - 'a');
    for(int i = 2 ; i <= cnt ; ++ i) add(pre[i], i);
    ans = (ll) n * (n - 1) * (n + 1) / 2;
    dfs(1);
    printf("%lld\n", ans);
}
