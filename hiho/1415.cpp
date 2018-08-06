// 题意：求两个字符串的最长公共子串
// 题解：第一个字符串建立后缀自动机，然后第二个串在上面跑，并更新答案
// 标签：后缀树, 后缀数组, 后缀自动机

#include <bits/stdc++.h>

using namespace std;

const int N = 100010 * 2;

int n, a[N], pre[N], len[N], p, np, q, nq, last = 1, cnt = 1;

map<int, int> ch[N];

int nd(int l) { return len[++ cnt] = l, cnt; }

void ins(int v) {
    last = np = nd(len[p = last] + 1);
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

char s[N], ss[N];

int main() {
    int ans = 0;
    scanf("%s%s", s + 1, ss + 1);
    for(int i = 1 ; s[i] ; ++ i) ins(s[i] - 'a');
    for(int i = 1, p = 1, l = 0 ; ss[i] ; ++ i) {
        int c = ss[i] - 'a';
        if(ch[p][c]) {
            p = ch[p][c];
            ++ l;
        } else {
            while(p && !ch[p][c]) p = pre[p];
            if(!p) p = 1, l = 0;
            else {
                l = len[p] + 1;
                p = ch[p][c];
            }
        }
        ans = max(ans, l);
    }
    printf("%d\n", ans);
}
