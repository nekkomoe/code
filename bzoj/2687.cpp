#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

struct LN {
    int l, r;
} ln[N];
ll ans;
bool cmp(LN a, LN b) {
    return a.l == b.l ? a.r > b.r : a.l < b.l;
}

int n;

void sol(int l, int r, int ql, int qr) {
    if(l >= r) return ;
    int mid = (l + r) >> 1, pos = 0;
    ll val = -1;
    for(int i = ql ; i <= min(mid - 1, qr) ; ++ i) {
        if(ln[i].r < ln[mid].l) continue;
        ll tmp = (ll) (ln[mid].r - ln[i].l) * (ln[i].r - ln[mid].l);
        ans = max(ans, tmp);
        if(tmp > val) {
            val = tmp;
            pos = i;
        }
    }
    if(pos) {
        sol(l, mid, ql, pos);
        sol(mid + 1, r, pos, qr);
    } else {
        sol(l, mid, ql, qr);
        sol(mid + 1, r, ql, qr);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &ln[i].l, &ln[i].r);
    }
    sort(ln + 1, ln + 1 + n, cmp);
    vector<LN> tmp;
    for(int i = 1, mxr = -1, pos = 0 ; i <= n ; ++ i) {
        if(ln[i].r > mxr) {
            tmp.push_back(ln[i]);
            mxr = ln[i].r;
            pos = i;
        } else {
            ans = max(ans, (ll) (ln[i].r - ln[i].l) * (ln[pos].r - ln[pos].l));
        }
    }
    n = tmp.size();
    for(int i = 1 ; i <= n ; ++ i) {
        ln[i] = tmp[i - 1];
    }
    sol(1, n, 1, n);
    printf("%lld\n", ans);
}
