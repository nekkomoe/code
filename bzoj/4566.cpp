// 题意：求两个字符串的相同子串个数
// 题解：SAM上计算匹配串的贡献
// 标签：SAM

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 200000 * 2 + 10;

int n1, n2, pre[N], ch[N][30], len[N], sz[N], last = 1, cnt = 1;

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
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

char s1[N], s2[N];

int tmp[N], bak[N];

ll sum[N], ans;

void topo() {
    for(int i = 1 ; i <= cnt ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= cnt ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = cnt ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = cnt ; i ; -- i) {
        int x = bak[i];
        sz[pre[x]] += sz[x];
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        int x = bak[i];
        sum[x] = sum[pre[x]] + 1ll * sz[x] * (len[x] - len[pre[x]]);
    }
}

void sol() {
    for(int i = 1, p = 1, l = 0 ; i <= n2 ; ++ i) {
        int c = s2[i] - 'a';
        if(ch[p][c]) {
            ++ l;
            p = ch[p][c];
        } else {
            while(p && !ch[p][c]) p = pre[p];
            if(p) {
                l = len[p] + 1;
                p = ch[p][c];
            } else {
                p = 1, l = 0;
            }
        }
        ans += sum[pre[p]] + 1ll * sz[p] * (l - len[pre[p]]);
    }
}

int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    n1 = strlen(s1 + 1), n2 = strlen(s2 + 1);
    for(int i = 1 ; i <= n1 ; ++ i) ins(s1[i] - 'a');
    topo();
    sol();
    printf("%lld\n", ans);
}
