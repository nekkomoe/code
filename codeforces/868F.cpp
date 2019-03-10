#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll N = 1e5 + 10;

ll a[N], f[N], ans[N], ql, qr, cost, n, k, cnt[N];

ll ins(ll x) {
    return cnt[x] ++;
}

ll rem(ll x) {
    return -- cnt[x];
}

void neko(ll l, ll r) {
    while(ql > l) cost += ins(a[-- ql]);
    while(qr < r) cost += ins(a[++ qr]);
    while(ql < l) cost -= rem(a[ql ++]);
    while(qr > r) cost -= rem(a[qr --]);
}

void sol(ll l, ll r, ll cl, ll cr) {
    if(l > r) return ;
    ll mid = (l + r) >> 1, pos = cl;
    for(ll i = min(cr + 1, mid) ; i > cl ; -- i) {
        neko(i, mid);
        ll val = f[i - 1] + cost;
        if(val < ans[mid]) {
            ans[mid] = val;
            pos = i - 1;
        }
    }
    sol(l, mid - 1, cl, pos), sol(mid + 1, r, pos, cr);
}

int main() {
    cin >> n >> k;
    for(ll i = 1 ; i <= n ; ++ i) cin >> a[i];
    for(ll i = 1 ; i <= n ; ++ i) ans[i] = ans[i - 1] + ins(a[i]);
    ql = 1, qr = n, cost = ans[n];

    for(ll i = 2 ; i <= k ; ++ i) {
        memcpy(f, ans, sizeof f);
        memset(ans, 0x3f, sizeof ans);
        sol(1, n, 0, n - 1);
    }

    cout << ans[n] << endl;
}
