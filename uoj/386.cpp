#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7, N = 2e5 + 10;

ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a) {
        if(b & 1) {
            r = r * a;
        }
    }
    return r;
}

ll getinv(ll n) {
    return pw(n, mod - 2);
}

void upd(ll &a, ll b) {
    a = (a + b) % mod;
}

int n, m, ds, dv;

int L[N], R[N];
void del(int x) {
    R[L[x]] = R[x];
    L[R[x]] = L[x];
}
struct FIXED {
    int id, s, v;
} a[N], b[N]; // 第一个按照权值排序，第二个按照大小排序
FIXED sta[N];

ll calc(ll S, ll V) {
    return pw(V, dv) - pw(S, ds);
}
ll s[N], ans = 0xcfcfcfcfcfcfcfcfll;

int main() {
    scanf("%d%d%d%d", &n, &m, &ds, &dv);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d", &a[i].s, &a[i].v);
    }
    sort(a + 1, a + 1 + n, [&](FIXED x, FIXED y) { return x.s < y.s; });
    for(int i = 1 ; i <= n ; ++ i) {
        a[i].id = i;
        b[i] = a[i];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        s[i] = s[i - 1] + a[i].v;
    }
    // for(int i = m ; i <= n ; ++ i) {
    //     ans = max(ans, calc(a[i].s - a[i - m + 1].s, s[i] - s[i - m]));
    // }
    for(int i = 1 ; i <= n ; ++ i) {
        ll s = 0;
        for(int j = i ; j <= min(n, i + m - 1) ; ++ j) {
            s += a[j].v;
            // ???????
            ans = max(ans, calc(a[j].s - a[i].s, s));
        }
    }
    sort(a + 1, a + 1 + n, [&](FIXED x, FIXED y) { return x.v < y.v; });
    R[0] = 1, L[n + 1] = n;
    for(int i = 1 ; i <= n ; ++ i) {
        L[i] = i - 1;
        R[i] = i + 1;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int top = 0;
        for(int j = a[i].id, tot = 1 ; tot <= m && j >= 1 ; j = L[j], ++ tot) {
            sta[++ top] = b[j];
        }
        reverse(sta + 1, sta + 1 + top);
        for(int j = R[a[i].id], tot = 2 ; tot <= m && j <= n ; j = R[j], ++ tot) {
            sta[++ top] = b[j];
        }
        for(int j = 1 ; j <= top ; ++ j) {
            s[j] = s[j - 1] + sta[j].v;
        }
        for(int j = m ; j <= top ; ++ j) {
            ans = max(ans, calc(sta[j].s - sta[j - m + 1].s, s[j] - s[j - m]));
        }
        del(a[i].id);
    }
    printf("%lld\n", ans);
}
