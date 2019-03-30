#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 3e5 + 10;

int n, q, a[N];

int lc[N], rc[N], sz[N], fix[N];
ll sum[N], val[N];
typedef pair<ll, int> pli; 
pli nek[N];

int upd(int x) {
    sz[x] = sz[lc[x]] + sz[rc[x]] + 1;
    sum[x] = sum[lc[x]] + sum[rc[x]] + val[x];
    nek[x] = min(min(
        lc[x] ? nek[lc[x]] : nek[0],
        rc[x] ? pli(sum[lc[x]] + val[x] + nek[rc[x]].first, sz[lc[x]] + 1 + nek[rc[x]].second) : nek[0]),
        pli(sum[lc[x]] + val[x], sz[lc[x]] + 1)
    );
    // printf("upd x = %d, nek = %d, %d, lc = %d, rc = %d\n", x, int(nek[x].first), nek[x].second, lc[x], rc[x]);
    return x;
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    if(fix[x] < fix[y]) {
        rc[x] = merge(rc[x], y);
        return upd(x);
    } else {
        lc[y] = merge(x, lc[y]);
        return upd(y);
    }
}

pair<int, int> split(int x, int k) {
    pair<int, int> res;
    if(x) {
        if(sz[lc[x]] >= k) {
            res = split(lc[x], k);
            lc[x] = res.second;
            res.second = upd(x);
        } else {
            res = split(rc[x], k - 1 - sz[lc[x]]);
            rc[x] = res.first;
            res.first = upd(x);
        }
    }
    return res;
}
int root;
void dfs(int u) {
    if(!u) return ;
    dfs(lc[u]);
    printf("%lld ", val[u]);
    dfs(rc[u]);
}

int main() {
    nek[0] = pli(0x3f3f3f3f, 0x3f3f3f3f);
    srand((unsigned long long) new char);
// #ifdef ONLINE_JUDGE
//     freopen("inversion.in", "r", stdin);
//     freopen("inversion.out", "w", stdout);
// #else
    // freopen("data.in", "r", stdin);
// #endif

    scanf("%d%d", &n, &q);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        sum[i] = val[i] = n - 2 * a[i] + 1;
        sz[i] = 1;
        fix[i] = i;
        nek[i] = pli(val[i], 1);
    }
    
    random_shuffle(fix + 1, fix + 1 + n);
    for(int i = 1 ; i <= n ; ++ i) {
        root = merge(root, i);
        // printf("root = %d\n", root);
        // dfs(root), puts("");
        // pli ans = min(nek[root], pli(0, 0));
        // printf("%lld, %d\n", ans.first, ans.second);
        // cout << nek[root].first << ", " << nek[root].second << endl;
        // puts("");
    }
    // return 0;

    while(q --) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        if(k) {
            pli x = split(root, r);
            pli y = split(x.first, l - 1);
            pli z = split(y.second, k);
            root = merge(merge(y.first, z.second), merge(z.first, x.second));
        }
//        dfs(root), puts("");
        pli ans = min(nek[root], pli(0, 0));
        printf("%d\n", ans.second);
    }
}
