#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;

ll x_1, x_2, x0, m, a, c, l1, r1, l2, r2;

ll cnt1[N], cnt2[N];

ll pos, len, vis[N], clk, val;

void upd(ll &x) {
    x = (a * x + c) % m;
}

void getloop(ll x) {
    while(1) {
        if(vis[x]) {
            pos = vis[x] - 1;
            val = x;
            len = clk + 1 - vis[x];
            return ;
        }
        vis[x] = ++ clk;
        upd(x);
    }
}

ll fafa(ll &inpx, ll i, ll tar, ll *cnt) {

    // ll tmp = 0, x = inpx;
    // do {
    //     tmp += x;
    //     cnt[x] ++;
    //     inpx = x;
    //     upd(x), ++ i;
    // } while(i <= tar);
    // return tmp;

    ll res = 0, x = inpx;
    while(i <= tar && i < pos) {
        cnt[x] ++;
        res += x;
        inpx = x;
        upd(x);
        ++ i;
    }
    if(i > tar) return res;

    while(i <= tar && (i - pos) % len != 0) {
        cnt[x] ++;
        res += x;
        inpx = x;
        upd(x);
        ++ i;
    }
    if(i > tar) return res;

    // i + k * len <= tar
    tar = tar - i + 1;
    ll k = tar / len;
    tar %= len;
    
    ll val = :: val;
    for(int i = 1 ; i <= len ; ++ i) {
        res += val * k;
        cnt[val] += k;
        inpx = val;
        upd(val);
    }

    if(k) {
        x = :: val;
    }
    while(tar --) {
        res += x;
        cnt[x] ++;
        inpx = x;
        upd(x);
    }

    return res;
}

ll rem[N];

void runprog() {

    ll ans = 0;

    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &m, &a, &c, &x0, &l1, &r1, &l2, &r2);

    getloop(x0);

    // printf("pos = %lld, len = %lld, val = %lld\n", pos, len, val);
    // for(ll i = 1, x = x0 ; i <= 20 ; ++ i) {
    //     printf("%lld ", x);
    //     upd(x);
    // } puts("");

    x_1 = x0, x_2 = x0;

    fafa(x_1, 0, l1, rem);
    fafa(x_2, 0, l2, rem);

    ans = fafa(x_1, l1, r1, cnt1);
    ans *= r2 - l2 + 1;

    fafa(x_2, l2, r2, cnt2);

    for(int i = 1 ; i <= m ; ++ i) {
        cnt1[i] += cnt1[i - 1];
    }

    for(ll a = 0 ; a <= m ; ++ a) {
        for(ll b = 1 ; b <= m + 1 && a * b <= m ; ++ b) {
            ll l = a * b, r = min(m, (a + 1) * b - 1);
            ll cnt = 0;
            if(r >= 0) {
                cnt += cnt1[r];
            }
            if(l - 1 >= 0) {
                cnt -= cnt1[l - 1];
            }

            ans += - a * b * cnt * cnt2[b - 1];
        }
    }

    for(int i = 0 ; i <= m ; ++ i) {
        cnt1[i] = cnt2[i] = vis[i] = 0;
        clk = 0;
    }

    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    for(int i = 1 ; i <= t ; ++ i) {
        printf("Case #%d: ", i);
        runprog();
    }
}
