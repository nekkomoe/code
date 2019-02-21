#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
 
const int mod = 998244353, N = 3e6;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
const ll inv = pw(10000, mod - 2);
ll ans;
int n, rk[N], val[N], val_cnt, sz[N], ch[N][2], fa[N];
ll p[N];
 
int root[N], lc[N], rc[N];
ll sum[N], tag[N], nd_cnt;
 
void add_tag(int x, ll neko) {
    if(!x) return ;
    (sum[x] *= neko % mod) %= mod;
    (tag[x] *= neko % mod) %= mod;
}
 
void push(int x) {
    if(!x) return ;
    if(tag[x] != 1) {
        add_tag(lc[x], tag[x]), add_tag(rc[x], tag[x]);
        tag[x] = 1;
    }
}
 
void upd(int x) {
    if(!x) return ;
    sum[x] = (sum[lc[x]] + sum[rc[x]]) % mod;
}
 
void modify(int &x, int l, int r, int pos, int val) {
    if(!x) x = ++ nd_cnt;
    push(x);
    int mid = (l + r) >> 1;
    if(l == r) {
        (sum[x] += val) %= mod;
        return ;
    } else if(pos <= mid) {
        modify(lc[x], l, mid, pos, val);
    } else {
        modify(rc[x], mid + 1, r, pos, val);
    }
    upd(x);
}
 
int merge(int x, int y, ll sumx, ll sumy, ll min, ll max) {
    if(!x) {
        add_tag(y, sumx);
        return y;
    }
    if(!y) {
        add_tag(x, sumy);
        return x;
    }
    push(x), push(y);
    ll t_x[2] = { sum[lc[x]], sum[rc[x]] };
    ll t_y[2] = { sum[lc[y]], sum[rc[y]] };
    lc[x] = merge(lc[x], lc[y], (sumx + min * t_x[1]) % mod, (sumy + min * t_y[1]) % mod, min, max);
    rc[x] = merge(rc[x], rc[y], (sumx + max * t_x[0]) % mod, (sumy + max * t_y[0]) % mod, min, max);
    upd(x);
    return x;
}
 
void dfs(int u) {
    if(!u) return ;
    dfs(ch[u][0]), dfs(ch[u][1]);
    if(sz[u] == 0) {
        modify(root[u], 1, val_cnt, rk[u], 1);
    } else if(sz[u] == 1) {
        root[u] = root[ch[u][0]];
    } else {
        root[u] = merge(root[ch[u][0]], root[ch[u][1]], 0ll, 0ll, 1 - p[u], p[u]);
    }
}
 
void go(int x, int l, int r) {
    if(!x) {
        return ;
    } else if(l == r) {
        (ans += (ll) l * val[l] % mod * sum[x] % mod * sum[x] % mod) %= mod;
    } else {
        int mid = (l + r) >> 1;
        push(x);
        go(lc[x], l, mid), go(rc[x], mid + 1, r);
    }
}
 
int main() {
    for(int i = 1 ; i < N ; ++ i) tag[i] = 1;
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &fa[i]);
        ch[fa[i]][sz[fa[i]] ++] = i;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        int x; scanf("%d", &x);
        if(sz[i]) {
            p[i] = x * inv % mod;
        } else {
            rk[i] = val[++ val_cnt] = x;
        }
    }
    sort(val + 1, val + 1 + val_cnt);
    for(int i = 1 ; i <= n ; ++ i) {
        rk[i] = lower_bound(val + 1, val + 1 + val_cnt, rk[i]) - val;
    }
 
    dfs(1);
    go(root[1], 1, val_cnt);
    printf("%lld\n", (ans % mod + mod) % mod);
}
