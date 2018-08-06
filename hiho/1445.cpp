#include <bits/stdc++.h>

typedef long long ll;

const int N = 1000000 * 2 + 10;

int pre[N], ch[N][30], len[N], last = 1, cnt = 1;

int nd(int l) {
    return len[++ cnt] = l, cnt;
}

void ins(int c) {
    int p, np, q, nq;
    pre[np = last = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), memcpy(ch[nq], ch[q], sizeof ch[q]), pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

ll ans;

char s[N];

int main() {
    int n = strlen(s + scanf("%s", s + 1));
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a');
    for(int i = 1 ; i <= cnt ; ++ i) ans += len[i] - len[pre[i]];
    printf("%lld\n", ans);
}
