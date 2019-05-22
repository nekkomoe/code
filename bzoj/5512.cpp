// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
int n, last = 1, cnt = 1, pre[N], len[N], sz[N], tmp[N], bak[N], ch[N][26];

int nd(int x) {
    return len[++ cnt] = x, cnt;
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
            pre[nq] = pre[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[np] = pre[q] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

char str[N];
int nek[N], k;

void runprog() {
    scanf("%s%d", str + 1, &k);
    n = strlen(str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        ins(str[i] - 'a');
    }
    for(int i = cnt ; i ; -- i) {
        ++ tmp[len[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        tmp[i] += tmp[i - 1];
    }
    for(int i = cnt ; i ; -- i) {
        bak[tmp[len[i]] --] = i;
    }
    for(int i = cnt ; i ; -- i) {
        int u = bak[i];
        if(pre[u]) {
            sz[pre[u]] += sz[u];
            if(sz[u] == k) {
                int l = len[pre[u]] + 1, r = len[u];
                nek[l] ++, nek[r + 1] --;
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        nek[i] += nek[i - 1];
    }
    int mx = 0, ans = -1;
    for(int i = n ; i >= 1 ; -- i) {
        if(nek[i] > mx) {
            mx = nek[i], ans = i;
        }
    }
    printf("%d\n", ans);
    for(int i = 1 ; i <= n ; ++ i) {
        nek[i] = 0;
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        pre[i] = len[i] = sz[i] = tmp[i] = bak[i] = 0;
        memset(ch[i], 0, sizeof ch[i]);
    }
    last = cnt = 1;
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
