#include "bits/stdc++.h"
using namespace std;

const int N = 40010;

int a[N], bit[N], f[N], ans[N], ql, qr, cost, n, k;

int ask(int x) {
    int res = 0;
    for( ; x ; x -= x & -x) {
        res += bit[x];
    }
    return res;
}

void chg(int x, int y) {
    for( ; x <= n ; x += x & -x) {
        bit[x] += y;
    }
}

void neko(int l, int r) {
    while(ql > l) cost += ask(a[-- ql] - 1), chg(a[ql], 1); 
    while(qr < r) cost += ask(n) - ask(a[++ qr]), chg(a[qr], 1);
    while(ql < l) chg(a[ql], -1), cost -= ask(a[ql ++] - 1);
    while(qr > r) chg(a[qr], -1), cost -= ask(n) - ask(a[qr --]);
}

void sol(int l, int r, int cl, int cr) {
    if(l > r) return ;
    int mid = (l + r) >> 1, pos = cl;
    for(int i = min(cr + 1, mid) ; i > cl ; -- i) {
        neko(i, mid);
        int val = f[i - 1] + cost;
        if(val < ans[mid]) {
            ans[mid] = val;
            pos = i - 1;
        }
    }
    sol(l, mid - 1, cl, pos), sol(mid + 1, r, pos, cr);
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    for(int i = 1 ; i <= n ; ++ i) ans[i] = ans[i - 1] + ask(n) - ask(a[i]), chg(a[i], 1);
    ql = 1, qr = n, cost = ans[n];

    for(int i = 2 ; i <= k ; ++ i) {
        memcpy(f, ans, sizeof f);
        memset(ans, 0x3f, sizeof ans);
        sol(1, n, 0, n - 1);
    }

    printf("%d\n", ans[n]);
}
