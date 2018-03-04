// 题意：求严格/不严格第k大子串
// 题解：前缀树上dp
// 标签；SAM

#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 * 2 + 10;

int ch[N][30], pre[N], sz[N], len[N], last = 1, cnt = 1;

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int T, k, n, tmp[N], bak[N], sum[N];

char s[N];

void topo() {
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        if(T) sz[pre[x]] += sz[x];
        else sz[x] = 1;
    }
    sz[1] = 0;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        sum[x] = sz[x];
        for(int j = 0 ; j < 26 ; ++ j) sum[x] += sum[ch[x][j]];
    }
}

void dfs(int u, int k) {
    if(k <= sz[u]) return ;
    k -= sz[u];
    for(int i = 0 ; i < 26 ; ++ i) {
        int v = ch[u][i];
        if(v) {
            if(k <= sum[v]) {
                putchar(i + 'a');
                dfs(v, k);
                return ;
            }
            k -= sum[v];
        }
    }
}

int main() {
    scanf("%s", s + 1);
    scanf("%d%d", &T, &k);
    n = strlen(s + 1);
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a');
    topo(), dfs(1, k), puts("");
}
