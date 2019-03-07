#include "bits/stdc++.h"
using namespace std;
const int N = 1e6 + 10;

char s[N];
int p, q, np, nq, ch[N][2], last = 1, cnt = 1, pre[N], len[N];

int nd(int l) { return len[++ cnt] = l, cnt; } 
void ins(int c) {
    pre[last = np = nd(len[p = last] + 1)] = 1;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

int n, m, mat[N];

void init() {
    for(int i = 1, u = 1, len = 0 ; s[i] ; ++ i) {
        int c = s[i] - '0';
        if(ch[u][c]) u = ch[u][c], ++ len;
        else {
            while(!ch[u][c] && u) u = pre[u];
            if(u) {
                len = :: len[u] + 1, u = ch[u][c];
            } else {
                u = 1;
            }
        }
        mat[i] = len;
    }
}

int que[N], l, r, f[N];

int check(int L, int n) {
    l = 1, r = 0;
    for(int i = 1 ; i < L ; ++ i) f[i] = 0;
    for(int i = L ; i <= n ; ++ i) {
        f[i] = f[i - 1];
        while(l <= r && f[que[r]] - que[r] <= f[i - L] - (i - L)) -- r;
        que[++ r] = i - L;
        while(l <= r && que[l] < i - mat[i]) ++ l;
        if(l <= r) f[i] = max(f[i], f[que[l]] + i - que[l]);
    }
    return f[n] * 10 >= n * 9;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", s + 1);
        last = 1;
        for(int j = 1 ; s[j] ; ++ j) {
            ins(s[j] - '0');
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s + 1);
        init();
        int len = strlen(s + 1), l = 0, r = len, ans = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(check(mid, len)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        printf("%d\n", ans);
    }
}
