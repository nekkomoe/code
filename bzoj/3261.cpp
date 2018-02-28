// 题意：维护一个数列，支持两种操作：1. 在末尾添加一个数字 2. 查询 $ max(xor_{i=p}^{size} a_i) $ 且 $ l \le p \le r $
// 题解：可持久化trie维护区间01trie，然后在上面贪心
// 标签：可持久化trie，贪心，前缀和

#include <bits/stdc++.h>

using namespace std;

const int N = 1000010;

int n, m;

int ch[N * 20][2], tot, root[N], sz[N * 20];

void ins(int now, int last, int val) {
    for(int i = 25 ; ~ i ; -- i) {
        int c = (val >> i) & 1;
        ch[now][!c] = ch[last][!c];
        sz[now = ch[now][c] = ++ tot] = sz[last = ch[last][c]] + 1;
    }
}

int query(int l, int r, int val) {
    int ret = 0;
    for(int i = 25 ; ~ i ; -- i) {
        int c = (val >> i) & 1;
        if(sz[ch[r][!c]] - sz[ch[l][!c]]) {
            ret |= 1 << i;
            l = ch[l][!c], r = ch[r][!c];
        } else {
            l = ch[l][c], r = ch[r][c];
        }
    }
    return ret;
}

int sm;

int main() {
    ins(root[1] = ++ tot, 0, 0);
    scanf("%d%d", &n, &m);
    for(int i = 1, t ; i <= n ; ++ i) {
        scanf("%d", &t);
        ins(root[i + 1] = ++ tot, root[i], sm ^= t);
    }
    for(int i = 1, l, r, val ; i <= m ; ++ i) {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'A') {
            scanf("%d", &val), ++ n;
            ins(root[n + 1] = ++ tot, root[n], sm ^= val);
        } else {
            scanf("%d%d%d", &l, &r, &val);
            printf("%d\n", query(root[l - 1], root[r], val ^ sm));
        }
    }
}
