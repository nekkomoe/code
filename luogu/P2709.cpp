// luogu-judger-enable-o2
%:pragma GCC optimize(2)

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cctype>

using namespace std;

typedef long long ll;

const int N = 50010;

int n, m, k, a[N], len;

ll ans[N];

struct Q {
    int l, r, id, bel;
} q[N];

bool operator < (Q a, Q b) {
    return a.bel == b.bel ? a.r < b.r : a.bel < b.bel;
}

int read() {
    int x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

int cnt[N], res;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= n ; ++ i) a[i] = read();
    len = sqrt(n) + 1;
    for(int i = 1 ; i <= m ; ++ i) q[i].l = read(), q[i].r = read(), q[i].id = i, q[i].bel = q[i].id / len + 1;
    sort(q + 1, q + 1 + m);
    int l = q[1].l, r = q[1].r;
    for(int i = l ; i <= r ; ++ i) {
        res += 2 * cnt[a[i]] ++ + 1;
    }
    ans[q[1].id] = res;
    for(int i = 2 ; i <= m ; ++ i) {
        while(r < q[i].r) {
            res += 2 * cnt[a[++ r]] ++ + 1;
        }
        while(l > q[i].l) {
            res += 2 * cnt[a[-- l]] ++ + 1;
        }
        while(r > q[i].r) {
            res -= 2 * cnt[a[r --]] -- - 1;
        }
        while(l < q[i].l) {
            res -= 2 * cnt[a[l ++]] -- - 1;
        }
        ans[q[i].id] = res;
    }
    for(int i = 1 ; i <= m ; ++ i) printf("%lld\n", ans[i]);
}

