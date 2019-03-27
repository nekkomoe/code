#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, LEN = 320;
int n, m, q;

ll a[N], s[N];

int bel[N], L[N], R[N], cnt;

int que[N], lef[N], rig[N], l, r;

ll tag[N]; // 块都被加上了某个数
void build(int);
ll calc(ll a, ll b) {
    return a / b + (a % b != 0);
}
ll ans;
void getans() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        int l = lef[i], r = rig[i];
        while(l < r && (s[que[r]] + tag[i]) * que[r - 1] < (s[que[r - 1]] + tag[i]) * que[r]) -- r;
        ans = max(ans, calc(s[que[r]] + tag[i], que[r]));
        lef[i] = l, rig[i] = r;
    }
    printf("%lld\n", ans);
}

void range_modify(int pos, int val) {
    // [pos, n] += val
    for(int i = pos ; i <= R[bel[pos]] ; ++ i) s[i] += val;
    build(bel[pos]);
    for(int i = bel[pos] + 1 ; i <= cnt ; ++ i) {
        tag[i] += val;
    }
}

void build(int x) {
    int l = L[x], r = l - 1;

    for(int i = L[x] ; i <= R[x] ; ++ i) {
        while(l < r &&

            (s[que[r]] * que[r - 1] - s[que[r - 1]] * que[r]) * (i - que[r]) < (s[i] * que[r] - s[que[r]] * i) * (que[r] - que[r - 1])

            ) -- r;
        que[++ r] = i;
    }

    lef[x] = l, rig[x] = r;
}

int main() {
//    freopen("computer.in", "r", stdin);
//    freopen("computer.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);

    for(int i = 1 ; i <= n ; ++ i) {
        int x = bel[i] = (i - 1) / LEN + 1;
        if(!L[x]) L[x] = i;
        R[x] = i;
    }
    cnt = bel[n];

    for(int i = 1 ; i <= m ; ++ i) {
        int x; scanf("%d", &x);
        a[x] ++;
    }

    for(int i = 1 ; i <= n ; ++ i) {
        s[i] = s[i - 1] + a[i];
    }

    for(int i = 1 ; i <= cnt ; ++ i) {
        build(i);
    }

    getans();

    while(q --) {
        int x, y; scanf("%d%d", &x, &y);
        range_modify(y, x);
        getans();
    }
}
