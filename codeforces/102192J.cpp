#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int lim = 1e9;
const int N = 1e5 + 10;
int n, m;
int pre[N]; // 前缀单调栈结尾
int sub[N]; // 后缀单调栈开头
int mx[N];
int a[N];

int rt[N];
int lc[N * 35], rc[N * 35], tot;
int mn[N * 35];

void modify(int y, int x, int l, int r, int pos, int k) {
    lc[x] = lc[y], rc[x] = rc[y], mn[x] = min(mn[y], k);
    int mid = (l + r) >> 1;
    if(l == r) {
        return ;
    } else if(pos <= mid) {
        modify(lc[y], lc[x] = ++ tot, l, mid, pos, k);
    } else {
        modify(rc[y], rc[x] = ++ tot, mid + 1, r, pos, k);
    }
}

int ask(int x, int l, int r, int pos) {
    // > pos,mn
    if(!x || r < pos) return 0x3f3f3f3f;
    if(l >= pos) return mn[x];
    int mid = (l + r) >> 1;
    return min(ask(lc[x], l, mid, pos), ask(rc[x], mid + 1, r, pos));
}

void runprog() {
    for(int i = 0 ; i <= tot ; ++ i) {
        lc[i] = rc[i] = 0;
        mn[i] = 0x3f3f3f3f;
    }
    tot = 0;

    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        pre[i] = sub[i] = 0;
        mx[i] = max(mx[i - 1], a[i]);
    }

    for(int i = 0 ; i <= n + 1 ; ++ i) {
        rt[i] = 0;
    }
    for(int i = n ; i >= 1 ; -- i) {
        modify(rt[i + 1], rt[i] = ++ tot, 1, lim, a[i], i);
    }

    int lst = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        pre[i] = pre[lst] + (a[lst] < a[i]);
        if(a[lst] < a[i]) {
            lst = i;
        }
    }
    stack<int> sta;
    for(int i = n ; i >= 1 ; -- i) {
        while(sta.size() && sta.top() <= a[i]) sta.pop();
        sta.emplace(a[i]);
        sub[i] = sta.size();
    }

    while(m --) {
        int p, q; scanf("%d%d", &p, &q);
        // a[p] = q
        int lst = a[p - 1];
        int ans = pre[p - 1];

        // printf("preans = %d\n", pre[p - 1]);

        int mx = max(:: mx[p - 1], q);
        if(q > :: mx[p - 1]) ++ ans;

        int pos = -1;
        if(p + 1 <= n) {
            // printf("in [%d, %d] ask for >= %d\n", p + 1, n, mx + 1);
            // printf("mn = %d\n", mn[rt[p + 1]]);
            pos = ask(rt[p + 1], 1, lim, mx + 1);
            if(pos == 0x3f3f3f3f) {
                pos = -1;
            }
        }
        
        // printf("mx = %d\n", mx);
        // printf("pos = %d\n", pos);
        if(pos != -1) {
            ans += sub[pos];
            // printf("sub[%d] = %d\n", pos, sub[pos]);
        }
        printf("%d\n", ans);
    }
}

int main() {
    memset(mn, 0x3f, sizeof mn);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
