#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <cctype>
#include <bitset>

using namespace std;

typedef long long ll;

const int N = 2e5 + 10;

int n, m, pre[N], len[N], ch[N][30], sz[N], vis[N], tot = 1, last = 1;

char s[N];

int nd(int l) {
    return len[++ tot] = l, tot;
}

void ins(int c, int i) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), pre[nq] = pre[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]), pre[np] = pre[q] = nq, vis[nq] = vis[q], sz[nq] = sz[q];
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
    while(np && vis[np] != i) vis[np] = i, sz[np] ++, np = pre[np];
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        last = 1;
        for(int j = 1 ; s[j] ; ++ j) {
            ins(s[j] - 'a', i);
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", s + 1);
        int p = 1;
        for(int j = 1 ; s[j] ; ++ j) {
            int c = s[j] - 'a';
            if(ch[p][c]) {
                p = ch[p][c];
            } else goto nxt;
        }
        printf("%d\n", sz[p]);
        continue;
nxt:
        puts("0");
    }
}

