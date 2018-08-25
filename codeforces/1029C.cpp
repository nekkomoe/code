#include "bits/stdc++.h"
using namespace std;

const int N = 3e5 + 10;

int n, l[N], r[N], ans;

struct LN {
    int l, r;
} pre[N], sub[N];

LN calc(LN a, LN b) {
    if(a.l == -1 || b.l == -1) return (LN) { -1, -1 };
    if(a.r > b.r) swap(a, b);
    if(b.l <= a.l && a.r <= b.r) return a;
    if(a.r < b.l) return (LN) { -1, -1 };
    return (LN) { b.l, a.r};
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &l[i], &r[i]);
    }
    pre[0].l = 0, pre[0].r = 1e9;
    sub[n + 1] = pre[0];
    for(int i = 1 ; i <= n ; ++ i) {
        pre[i] = calc(pre[i - 1], (LN) { l[i], r[i] });
    }
    for(int i = n ; i ; -- i) {
        sub[i] = calc(sub[i + 1], (LN) { l[i], r[i] });
    }
    for(int i = 1 ; i <= n ; ++ i) {
        // cout << "pre: " << pre[i].l << ' ' << pre[i].r << endl;
        // cout << "sub: " << sub[i].l << ' ' << sub[i].r << endl;
        LN t = calc(pre[i - 1], sub[i + 1]);
        if(t.l != -1) ans = max(ans, t.r - t.l);
    }
    printf("%d\n", ans);
}
