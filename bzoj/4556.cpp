#include <bits/stdc++.h>

using namespace std;

const int N = 100010 * 2;

int pre[N], ch[N][30], sz[N], len[N];

char s[N];

int nd(int l) {
    static int tot = 1;
    if(l == -1) return tot;
    return len[++ tot] = l, tot;
}

void ins(int c) {
    static int last = 1;
    int p, np, q, nq;
    last = np = nd(len[p] + 1);
    pre[np] = sz[np] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        q = pre[np] = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q], pre[np] = pre[q] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p]; 
        }
    }
}

int head[N], rest[N], to[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot], rest[tot] = head[u], head[u] = tot;
}

int main() {
}
