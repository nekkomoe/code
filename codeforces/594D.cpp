#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e5 + 10, mod = 1e9 + 7;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
vector<int> pri[int(1e6) + 10];
int vis[int(1e6) + 10], n, q;
ll ans[N];
struct ASK {
    int l, r, id;
} ask[N];
bool operator < (ASK a, ASK b) {
    return a.r < b.r;
}
int lst[int(1e6) + 10], lim = 1, a[N];
ll inv[N], prod[N];

ll bit[int(1e6) + 10];

ll bitask(int x) {
    ll res = 1;
    for( ; x ; x -= x & -x) {
        res = res * bit[x] % mod;
    }
    return res;
}

void add(int x, ll y) {
    for( ; x <= lim ; x += x & -x) {
        bit[x] = bit[x] * y % mod;
    }
}

int main() {
    scanf("%d", &n);
    prod[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
        lim = max(lim, a[i]);
        prod[i] = prod[i - 1] * a[i] % mod;
    }
    for(int i = 2 ; i <= lim ; ++ i) {
        if(!vis[i]) {
            for(int j = i ; j <= lim ; j += i) {
                pri[j].push_back(i);
                vis[j] = 1;
            }
        }
    }
    for(int i = 0 ; i <= lim ; ++ i) {
        bit[i] = 1;
    }

    scanf("%d", &q);
    for(int i = 1 ; i <= q ; ++ i) {
        scanf("%d%d", &ask[i].l, &ask[i].r);
        ask[i].id = i;
    }

    sort(ask + 1, ask + 1 + q);

    for(int i = 1, j = 1 ; i <= q ; ++ i) {
        while(j <= n && j <= ask[i].r) {
            for(int k = 0 ; k < pri[a[j]].size() ; ++ k) {
                int p = pri[a[j]][k];
                add(j, p - 1);
                add(j, pw(p, mod - 2));
                if(lst[p]) {
                    add(lst[p], pw(p - 1, mod - 2));
                    add(lst[p], p);
                }
                lst[p] = j;
            }
            ++ j;
        }
        int l = ask[i].l, r = ask[i].r;
        ans[ask[i].id] =
            prod[r] * pw(prod[l - 1], mod - 2) % mod
            * bitask(r) % mod * pw(bitask(l - 1), mod - 2) % mod;
    }

    for(int i = 1 ; i <= q ; ++ i) {
        printf("%lld\n", (ans[i] + mod) % mod);
    }
}
