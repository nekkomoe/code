// 题意：给出一个长度为n的串s，如果s中的第p位开始的后缀和第q位开始的后缀的公共前缀长度为r，那么称p和q是r相似的。将p和q混合在一起时，p和q混合物的权值是a[p]*a[q]。输出x∈[0,n-1]的x相似方案数和x相似时的最大权值 
// 题解：后缀树上dp
// 标签：后缀树, 后缀自动机, 后缀数组

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 610000;

const int inf = 1e9 + 1;

int head[N], rest[N], to[N];

int sz[N], w[N], pre[N], ch[N][30], len[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int nd(int l) {
    static int tot = 1;
    if(l == -1) return tot;
    len[++ tot] = l;
    return tot;
}

void ins(int c, int ww) {
    int p, np, q, nq;
    static int last = 1;
    last = np = nd(len[p = last] + 1);
    sz[np] = pre[np] = 1, w[np] = ww;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        q = pre[np] = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), pre[nq] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int n, a[N];

char s[N];

ll as[N], ct[N], mx[N], mn[N];

void dfs(int u) {
    mx[u] = -inf, mn[u] = inf;
    if(sz[u]) mx[u] = mn[u] = w[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        dfs(v);
        if(mx[u] != -inf && mn[u] != inf && mx[v] != -inf && mn[v] != inf) {
            as[len[u]] = max(as[len[u]], max(mx[u] * mx[v], mn[u] * mn[v]));
        }
        mx[u] = max(mx[u], mx[v]), mn[u] = min(mn[u], mn[v]);
        ct[len[u]] += (ll) sz[u] * sz[v], sz[u] += sz[v];
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = n ; i >= 1 ; -- i) ins(s[i] - 'a', a[i]);
    for(int i = 2 ; i <= nd(-1) ; ++ i) add(pre[i], i);
    for(int i = 0 ; i <= n ; ++ i) as[i] = -1e18;
    dfs(1);
    for(int i = n - 1 ; i >= 0 ; -- i) as[i] = max(as[i], as[i + 1]), ct[i] += ct[i + 1];
    for(int i = 0 ; i <= n - 1 ; ++ i) if(ct[i]) printf("%lld %lld\n", ct[i], as[i]); else puts("0 0");
}
