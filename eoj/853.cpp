#include <bits/stdc++.h>
using namespace std;
// typedef long long ll;
#define ll int
const int mod = 998244353;
vector<int> ban[int(2e5 + 10)];
int n, m, k;
vector<int> g[int(2e5 + 10)];
void chkmul(ll &x, ll y) { x = (long long) x * y % mod; }
void upd(ll &x, ll y) { x = ((long long) x + y) % mod; }

long long pw(long long a, long long b) {
    long long r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) {
        if(b & 1) {
            r = r * a % mod;
        }
    }
    return r;
}
long long inv(long long x) {
    return pw(x, mod - 2);
}

// const int N = 3e7 + 10;
const int N = 21970814 + 3;

int tot, sum[N], lc[N], rc[N], add[N], mul[N]; // x * mul + add
// int val[N];

void tagitmul(int x, ll val) {
    chkmul(mul[x], val);
    chkmul(add[x], val);
}

int nd() {
    // printf("tot = %d\n", tot);
    ++ tot;
    mul[tot] = 1;
    return tot;
}

void push(int x, int l, int r, int tarson = 1) {
    if(!x) {
        return ;
    }

    if(tarson) {
        if(!lc[x] && l < r) {
            lc[x] = nd();
        }
        if(!rc[x] && l < r) {
            rc[x] = nd();
        }
    }

    if(mul[x] != 1) {
        chkmul(mul[lc[x]], mul[x]);
        chkmul(add[lc[x]], mul[x]);
        chkmul(mul[rc[x]], mul[x]);
        chkmul(add[rc[x]], mul[x]);
        chkmul(sum[x], mul[x]);
        // chkmul(val[x], mul[x]);
        mul[x] = 1;
    }
    if(add[x]) {
        upd(add[lc[x]], add[x]);
        upd(add[rc[x]], add[x]);
        upd(sum[x], (long long) (r - l + 1) * add[x] % mod);
        // upd(val[x], add[x]);
        add[x] = 0;
    }
}

int merge(int x, int y, int l, int r) {
    if(!x || !y) {
        return x | y;
    }
    if(!lc[y] && !rc[y]) {
        swap(x, y);
    }
    if(!lc[x] && !rc[x]) {
        push(x, l, r, 0);
        // tagitmul(y, val[x]);
        tagitmul(y, sum[x] * inv(r - l + 1) % mod);
        return y;
    }

    push(x, l, r), push(y, l, r);
    int mid = (l + r) >> 1;
    lc[x] = merge(lc[x], lc[y], l, mid);
    rc[x] = merge(rc[x], rc[y], mid + 1, r);
    push(lc[x], l, mid), push(rc[x], mid + 1, r);
    sum[x] = (sum[lc[x]] + sum[rc[x]]) % mod;
    return x;
}

void modify(int &x, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    if(!x) {
        x = nd();
    }
    push(x, l, r);
    if(l == r) {
        // val[x] = 0;
        sum[x] = 0;
        return ;
    } else if(pos <= mid) {
        modify(lc[x], l, mid, pos);
    } else {
        modify(rc[x], mid + 1, r, pos);
    }
    push(x, l, r), push(lc[x], l, mid), push(rc[x], mid + 1, r);
    sum[x] = (sum[lc[x]] + sum[rc[x]]) % mod;
}

int dfs(int u, int fa) {
    vector<int> ban = :: ban[u];
    sort(ban.begin(), ban.end());
    ban.erase(unique(ban.begin(), ban.end()), ban.end());

    int rt = nd();
    add[rt] = 1;

    for(int x: ban) {
        modify(rt, 1, m, x);
    }

    for(int v: g[u]) {
        if(v != fa) {
            int son = dfs(v, u);
            push(son, 1, m);
            ll S = sum[son];
            tagitmul(son, -1);
            upd(add[son], S);
            rt = merge(rt, son, 1, m);
        }
    }

    push(rt, 1, m);
    return rt;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1, x, y ; i <= k ; ++ i) {
        scanf("%d%d", &x, &y);
        ban[x].push_back(y);
    }
    int rt = dfs(1, 0);
    push(rt, 1, m);
    ll ans = sum[rt];
    printf("%d\n", (ans % mod + mod) % mod);
    // printf("tot = %d\n", tot);
}
