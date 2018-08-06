// 题意：求出现至少2次的不重叠子串最长长度
// 题解：模型转化为后缀树上的节点子树中后缀节点极值之差和当前代表长度的最小值的最大值
// 标签：后缀树, 后缀数组, 后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, a[N], pre[N], len[N], p, np, q, nq, last = 1, cnt = 1;

map<int, int> ch[N];

int mx[N], mn[N], d[N], ans;

int nd(int l) { return len[++ cnt] = l, cnt; }

void ins(int v, int t) {
    last = np = nd(len[p = last] + 1);
    mn[np] = mx[np] = t;
    pre[np] = 1;
    while(p && !ch[p][v]) ch[p][v] = np, p = pre[p];
    if(!p) return ;
    pre[np] = q = ch[p][v];
    if(len[p] + 1 != len[q]) {
        nq = nd(len[p] + 1);
        pre[nq] = pre[q], pre[q] = pre[np] = nq;
        ch[nq] = ch[q];
        while(p && ch[p][v] == q) ch[p][v] = nq , p = pre[p];
    }
}

void bfs() {
    queue<int> q;
    for(int i = 1 ; i <= cnt ; ++ i) ++ d[pre[i]];
    for(int i = 1 ; i <= cnt ; ++ i) if(!d[i]) q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        if(u <= 1) break;
        if(!-- d[pre[u]]) q.push(pre[u]);
        mx[pre[u]] = max(mx[pre[u]], mx[u]);
        mn[pre[u]] = min(mn[pre[u]], mn[u]);
        ans = max(ans, min(len[u], mx[u] - mn[u]));
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < N ; ++ i) mx[i] = 0xcfcfcfcf, mn[i] = 0x3f3f3f3f;
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) ins(a[i], i);
    bfs();
    printf("%d\n", ans);
}
