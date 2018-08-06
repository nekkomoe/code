#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 200010;

int n, k;

int ch[N][30], pre[N], len[N], sz[N], t[N], tot = 1, last = 1, pos[N];

int nd(int l) { return len[++ tot] = l, tot; }

void ins(int c, int i) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1, pos[np] = i;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), memcpy(ch[nq], ch[q], sizeof ch[q]), pre[nq] = pre[q], pre[np] = pre[q] = nq, sz[nq] = sz[q], t[nq] = t[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
    while(np && t[np] != i) t[np] = i, sz[np] ++, np = pre[np];
}

ll cnt[N], ans[N];

int bak[N], tmp[N];

char s[N];

int head[N], rest[N], to[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
    cnt[u] += cnt[pre[u]];
    ans[pos[u]] += cnt[u];
    for(int i = head[u] ; i ; i = rest[i]) dfs(to[i]);
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        last = 1;
        for(int j = 1 ; s[j] ; ++ j) ins(s[j] - 'a', i);
    }
    for(int i = 1 ; i <= tot ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= tot ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = tot ; i ; -- i) bak[tmp[len[i]] --] = i;

    for(int i = 2 ; i <= tot ; ++ i) {
        add(pre[i], i);
        if(sz[i] >= k) cnt[i] = len[i] - len[pre[i]];
    }
    dfs(1);
    for(int i = 1 ; i <= n ; ++ i) printf("%lld ", ans[i]);
}

