#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;

int pri[N], tot; bool vis[N];
ll sump[N];

void getpri() {
    int n = 5e6;
    for(int i = 2 ; i <= n ; ++ i) {
        if(!vis[i]) {
            pri[++ tot] = i;
            sump[tot] = sump[tot - 1] + i;
        }
        for(int j = 1 ; j <= tot ; ++ j) {
            if(pri[j] * i > n) break;
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}

int id1[N], id2[N], lim;
ll g[N], n, nek[N];

int gid(ll x) {
    return x <= lim ? id1[x] : id2[n / x];
}

ll sol(ll _n) {
    ll res = 0;
    n = _n;
    lim = sqrt(n);
    int m = 0;
    for(ll i = 1, j, val ; i <= n ; i = j + 1) {
        val = n / i, j = n / val;
        if(val <= lim) {
            id1[val] = ++ m;
        } else {
            id2[n / val] = ++ m;
        }
        nek[m] = val;
        g[m] = (ll) (2 + val) * (val - 1) / 2;
    }
    for(int i = 1 ; i <= tot ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if((ll) pri[i] * pri[i] > nek[j]) break;
            ll x = nek[j];
            if(j == 1) {
                res += g[gid(x / pri[i])] - sump[i - 1];
            }
            g[j] -= (ll) pri[i] * (g[gid(x / pri[i])] - sump[i - 1]);
        }
    }
    return res;
}

int main() {
    getpri();
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", sol(r) - sol(l - 1));
}
