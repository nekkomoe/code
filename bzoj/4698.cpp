#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m[N], a[N][N], len[N], ans, state[N];

struct SAM {
    int pre[N], len[N], cnt, last;
    map<int, int> ch[N];
    SAM() { cnt = last = 1; }
    int nd(int l) { return len[++ cnt] = l, cnt; }
    void ins(int c) {
        int p, np, q, nq;
        pre[np = last = nd(len[p = last] + 1)] = 1;
        while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
        if(p) {
            pre[np] = q = ch[p][c];
            if(len[p] + 1 != len[q]) {
                nq = nd(len[p] + 1);
                pre[nq] = pre[q], pre[np] = pre[q] = nq;
                ch[nq] = ch[q];
                while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
            }
        }
    }
} sam[N];

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &m[i]);
        for(int j = 1 ; j <= m[i] ; ++ j) scanf("%d", &a[i][j]);
        for(int j = 1 ; j < m[i] ; ++ j) sam[i].ins(a[i][j] -= a[i][j + 1]);
        m[i] --;
    }
    for(int i = 2 ; i <= n ; ++ i) state[i] = 1;
    for(int i = 1 ; i <= m[1] ; ++ i) {
        int c = a[1][i];
        int mn = m[1];
        for(int j = 2 ; j <= n ; ++ j) {
            int &p = state[j], &l = len[j];
            if(sam[j].ch[p][c]) p = sam[j].ch[p][c], ++ l;
            else {
                while(p && !sam[j].ch[p][c]) p = sam[j].pre[p];
                if(p) l = sam[j].len[p] + 1, p = sam[j].ch[p][c];
                else l = 0, p = 1;
            }
            mn = min(mn, l);
        }
        ans = max(ans, mn);
    }
    printf("%d\n", ans + 1);
}
