#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;

const int N = 1e5 + 10, mod = 1e9 + 9;

int n, k, a, b, c, d;
pr pts[N], val[N * 10];
int L[N * 10], R[N * 10], X[N * 10], lc[N * 10], rc[N * 10], tot;

pr upd(pr a, pr b) {
    return make_pair(a.second + b.second, max(a.first + b.second, a.second + b.first) + 1);
}

#define lc lc[id]
#define rc rc[id]

void build(int id, int l, int r) {
    int pos = l;
    for(int i = l ; i <= r ; ++ i) {
        if(pts[i].second > pts[pos].second) {
            pos = i;
        }
    }
    L[id] = pts[l].first;
    R[id] = pts[r].first;
    X[id] = pts[pos].first;
    if(l < pos) build(lc = ++ tot, l, pos - 1);
    if(pos < r) build(rc = ++ tot, pos + 1, r);
    val[id] = upd(val[lc], val[rc]);
}

pr ask(int id, int ql, int qr) {
    if(!id || qr < L[id] || ql > R[id]) return val[0];
    else if(ql <= L[id] && R[id] <= qr) return val[id];
    else if(qr < X[id]) return ask(lc, ql, qr);
    else if(ql > X[id]) return ask(rc, ql, qr);
    else return upd(ask(lc, ql, qr), ask(rc, ql, qr));
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%d%d", &pts[i].first, &pts[i].second);
    }
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for(int i = k + 1 ; i <= n ; ++ i) {
        pts[i].first = ((ll) a * pts[i - 1].first + b) % mod;
        pts[i].second = ((ll) c * pts[i - 1].second + d) % mod;
    }
    sort(pts + 1, pts + 1 + n);
    val[0] = make_pair(-1, 0);
    build(++ tot, 1, n);
    int q; scanf("%d", &q);
    while(q --) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", ask(1, l, r).second);
    }
}
