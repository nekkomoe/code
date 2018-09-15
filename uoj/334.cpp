// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 * 20 + 10;
int n, m, q;
typedef pair<int, int> p;
int fix[N], len[N], lc[N], rc[N], tot;
ll l[N], r[N];

int nd(ll l, ll r) {
    fix[++ tot] = rand();
    :: l[tot] = l, :: r[tot] = r;
    len[tot] = r - l + 1;
    return tot;
}

void up(int x) {
    len[x] = len[lc[x]] + len[rc[x]] + (r[x] - l[x] + 1);
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    if(fix[x] < fix[y]) {
        rc[x] = merge(rc[x], y);
        return up(x), x;
    } else {
        lc[y] = merge(x, lc[y]);
        return up(y), y;
    }
}

p prek(int x, int k) {
    p res;
    if(x) {
        if(len[lc[x]] + 1 <= k && k <= len[lc[x]] + (r[x] - l[x] + 1)) {
            ll L = l[x] + k - len[lc[x]], R = r[x];
            if(L <= R) {
                int y = nd(L, R);
                rc[y] = rc[x], rc[x] = 0;
                up(y);
                r[x] = L - 1;
                res.first = x, res.second = y;
            } else {
                res.first = x, res.second = rc[x], rc[x] = 0;
            }
        } else if(len[lc[x]] >= k) {
            res = prek(lc[x], k);
            lc[x] = res.second, res.second = x;
        } else {
            res = prek(rc[x], k - len[lc[x]] - (r[x] - l[x] + 1));
            rc[x] = res.first, res.first = x;
        }
        up(x);
    }
    return res;
}

int root[N], lst;

int main() {
    srand(1289218);
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        root[i] = nd(1ll * (i - 1) * m + 1, 1ll * i * m - 1);
        lst = merge(lst, nd(1ll * i * m, 1ll * i * m));
    }
    for(int i = 1 ; i <= q ; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        if(y == m) {
            p a = prek(lst, x - 1);
            p b = prek(a.second, 1);
            printf("%lld\n", l[b.first]);
            lst = merge(a.first, merge(b.second, b.first));
        } else {
            p a = prek(root[x], y - 1);
            p b = prek(a.second, 1);
            p c = prek(lst, x - 1);
            p d = prek(c.second, 1);
            
            printf("%lld\n", l[b.first]);
            root[x] = merge(a.first, merge(b.second, d.first));
            lst = merge(c.first, merge(d.second, b.first));
        }
    }
}
