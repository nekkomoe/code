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

int n, m, pre[N], len[N], ch[N][30], tot = 1, last = 1, ans;

char s1[N], s2[N];

int nd(int l) {
    return len[++ tot] = l, tot;
}

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), pre[nq] = pre[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]), pre[np] = pre[q] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    for(int i = 1 ; s1[i] ; ++ i) ins(s1[i] - 'a');
    for(int i = 1, p = 1, l = 0 ; s2[i] ; ++ i) {
        int c = s2[i] - 'a';
        if(ch[p][c]) {
            l ++, p = ch[p][c];
        } else {
            while(p && !ch[p][c]) p = pre[p];
            if(p) l = len[p] + 1, p = ch[p][c];
            else l = 0, p = 1;
        }
        ans = max(ans, l);
    }
    printf("%d\n", ans);
}

