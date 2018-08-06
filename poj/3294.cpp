#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

const int N = 4e5 + 10;

int n, m, pre[N], ch[N][30], len[N], tot, last, ans, nxt[N], sz[N];

char s[N];

void init() {
    memset(pre, 0, sizeof pre);
    memset(ch, 0, sizeof ch);
    memset(len, 0, sizeof len);
    memset(nxt, 0, sizeof nxt);
    memset(sz, 0, sizeof sz);
    tot = last = 1;
    ans = 0;
}

int nd(int l) { return len[++ tot] = l, tot;  }

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            sz[nq] = sz[q];
            nxt[nq] = nxt[q];
            pre[nq] = pre[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
    while(np) {
        if(nxt[np] != m) nxt[np] = m, ++ sz[np];
        else break;
        np = pre[np];
    }
}

void dfs(int u, int d) {
    if(d != len[u] || d > ans) return ;
    else if(ans == len[u] && sz[u] > n / 2) puts(s);
    else for(int i = 0 ; i < 26 ; ++ i) if(ch[u][i]) s[d] = i + 'a', dfs(ch[u][i], d + 1), s[d] = 0;
}

void sol() {
    init();
    for(m = 1 ; m <= n ; ++ m) {
        last = 1;
        scanf("%s", s + 1);
        for(int j = 1 ; s[j] ; ++ j) {
            ins(s[j] - 'a');
        }
    }
    memset(s, 0, sizeof s);
    for(int p = 1 ; p <= tot ; ++ p) {
        if(sz[p] > n / 2) ans = max(ans, len[p]);
    }
    if(!ans) puts("?");
    else dfs(1, 0);
    puts("");
}

int main() {
    while(scanf("%d", &n), n) sol();
}

