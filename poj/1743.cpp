#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

const int N = 20000 * 2 + 10;

int n;

int pre[N], len[N], last = 1, tot = 1;

int ch[N][180];

int tmp[N], bak[N];

int a[N], mx[N], mn[N];

int ans;

int nd(int l) {
    return len[++ tot] = l, tot;
}

void ins(int c, int i) {
    int p, np, q, nq;

    pre[np = last = nd(len[p = last] + 1)] = 1, mx[np] = mn[np] = i;

    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];

    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1), memcpy(ch[nq], ch[q], sizeof ch[q]), pre[nq] = pre[q], pre[q] = pre[np] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

void sol() {
    ans = 0;
    tot = last = 1;
    memset(ch, 0, sizeof ch);
    memset(pre, 0, sizeof pre);
    memset(len, 0, sizeof len);
    memset(tmp, 0, sizeof tmp);
    memset(bak, 0, sizeof bak);
    memset(mx, 0, sizeof mx);
    memset(mn, 0x3f, sizeof mn);

    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i < n ; ++ i) ins(a[i + 1] - a[i] + 88, i);
    for(int i = 1 ; i <= tot ; ++ i) tmp[len[i]] ++;
    for(int i = 1 ; i <= tot ; ++ i) tmp[i] += tmp[i - 1];
    for(int i = tot ; i ; -- i) bak[tmp[len[i]] --] = i;
    for(int i = tot ; i ; -- i) {
        int x = bak[i];
        mx[pre[x]] = max(mx[pre[x]], mx[x]);
        mn[pre[x]] = min(mn[pre[x]], mn[x]);
        ans = max(ans, min(len[x], mx[x] - mn[x]));
    }
}

int main() {
    while(scanf("%d", &n) == 1 && n) {
        sol();
        printf("%d\n", ans < 4 ? 0 : ans + 1);
    }
}
