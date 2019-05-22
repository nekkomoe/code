#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 4e6 + 10;

int ch[N][26], len[N], pre[N], last = 1, cnt = 1, bak[N], tmp[N], sz[N];

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    int p, np, q, nq;
    pre[last = np = nd(len[p = last] + 1)] = 1;
    sz[np] = 1;
    while(p && !ch[p][c]) {
        ch[p][c] = np;
        p = pre[p];
    }
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[nq] = pre[q];
            pre[np] = pre[q] = nq;
            while(p && ch[p][c] == q) {
                ch[p][c] = nq;
                p = pre[p];
            }
        }
    }
}

char str[N];
int clk, dfn[N];
ll ans;
int u, l, n;
void fed(int c) {
    while(u && !ch[u][c]) {
        u = pre[u], l = len[u];
    }
    if(u) {
        u = ch[u][c], ++ l;
    } else {
        u = 1, l = 0;
    }
}
void calc() {
    if(l == n && dfn[u] < clk) {
        dfn[u] = clk;
        ans += sz[u];
    }
}
void rem() {
    if(l > n) {
        -- l;
        if(l == len[pre[u]]) {
            u = pre[u];
        }
    }
}

void runprog() {
    ans = 0;
    ++ clk;
    scanf("%s", str + 1);
    n = strlen(str + 1);
    u = 1, l = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        fed(str[i] - 'a');
    }
    calc();
    for(int i = 1 ; i <= n ; ++ i) {
        fed(str[i] - 'a');
        rem();
        calc();
    }
    printf("%lld\n", ans);
}

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        ins(str[i] - 'a');
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        tmp[len[i]] ++;
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
        }
    }

    // for(int i = 1 ; i <= cnt ; ++ i) {
    //     printf("%d %d %d\n", len[i], pre[i], sz[i]);
    // }
    int q; scanf("%d", &q);
    while(q --) {
        runprog();
    }
}
