// 题意：求字符串的最小表示法
// 题解：复制一遍之后SAM上跑最小的n次
// 标签：后缀数组，后缀树，后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 300010 * 4;

int p, q, np, nq, last = 1, cnt = 1, len[N], pre[N], ep[N];

map<int, int> ch[N];

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1, ep[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            ch[nq] = ch[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int n, a[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), ins(a[i]);
    for(int i = 1 ; i <= n ; ++ i) ins(a[i]);
    for(int i = 1, p = 1 ; i <= n ; ++ i) {
        printf("%d", ch[p].begin() -> first);
        if(i < n) putchar(' ');
        p = ch[p].begin() -> second;
    }
}
