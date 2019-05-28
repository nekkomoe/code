#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const int N = 4e5 + 10;

int n;
ll a[N], b[N], w[N], l[N], r[N], p[N], ans, f[N];
int head[N], rest[N], to[N], tot = 1;
void add_sig(int u, int v, ll w) {
    to[++ tot] = v, f[tot] = w, rest[tot] = head[u], head[u] = tot;
}
void add(int u, int v, ll w) {
    add_sig(u, v, w), add_sig(v, u, 0);
}
int s, t, cnt;
int dis[N];
queue<int> q;
int bfs() {
    for(int i = 1 ; i <= cnt ; ++ i) {
        dis[i] = -1;
    }
    dis[s] = 1, q.push(s);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(dis[v] == -1 && f[i]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}
ll dfs(int u, ll flow) {
    if(u == t || !flow) {
        return flow;
    }
    ll use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(dis[v] == dis[u] + 1 && f[i]) {
            ll a = dfs(v, min(flow - use, f[i]));
            f[i] -= a, f[i ^ 1] += a, use += a;
            if(use == flow) {
                break;
            }
        }
    }
    if(!use) {
        dis[u] = -1;
    }
    return use;
}

ll mxflow() {
    ll res = 0;
    while(bfs()) {
        res += dfs(s, inf);
    }
    return res;
}

int lim, rt[N], nek, nd[N], lc[N], rc[N];

void ask(int u, int l, int r, int ql, int qr, int tar) {
    if(!u) {
        return ;
    }
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        add(tar, nd[u], inf);
    } else if(qr <= mid) {
        ask(lc[u], l, mid, ql, qr, tar);
    } else if(ql >= mid + 1) {
        ask(rc[u], mid + 1, r, ql, qr, tar);
    } else {
        ask(lc[u], l, mid, ql, mid, tar);
        ask(rc[u], mid + 1, r, mid + 1, qr, tar);
    }
}

void ins(int &now, int last, int l, int r, int pos, int tar) {
    int mid = (l + r) >> 1;
    
    now = ++ nek, nd[now] = ++ cnt;

    lc[now] = lc[last], rc[now] = rc[last];

    if(l == r) {
        add(nd[now], tar, inf);
        return ;
    } else if(pos <= mid) {
        ins(lc[now], lc[last], l, mid, pos, tar);
    } else {
        ins(rc[now], rc[last], mid + 1, r, pos, tar);
    }

    if(lc[now]) {
        add(nd[now], nd[lc[now]], inf);
    }
    if(rc[now]) {
        add(nd[now], nd[rc[now]], inf);
    }
}

void build() {

    vector<pair<ll, ll> > num;

    for(int i = 1 ; i <= n ; ++ i) {
        num.push_back(make_pair(a[i], i));
        num.push_back(make_pair(l[i], -inf));
        num.push_back(make_pair(r[i], inf));
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), make_pair(a[i], (ll) i)) - num.begin() + 1;
        l[i] = lower_bound(num.begin(), num.end(), make_pair(l[i], -inf)) - num.begin() + 1;
        r[i] = lower_bound(num.begin(), num.end(), make_pair(r[i], inf)) - num.begin() + 1;
    }

    cnt = 2 * n;
    s = ++ cnt, t = ++ cnt;
    for(int i = 1 ; i <= n ; ++ i) {
        add(s, i, b[i]);
        add(i, t, w[i]);
        add(i, n + i, p[i]);

        ask(rt[i - 1], 1, lim, l[i], r[i], n + i);
        ins(rt[i], rt[i - 1], 1, lim, a[i], i);

        // for(int j = 1 ; j < i ; ++ j) {
        //     if(l[i] <= a[j] && a[j] <= r[i]) {
        //         add(n + i, j, inf);
        //     }
        // }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%lld%lld%lld%lld%lld%lld", &a[i], &b[i], &w[i], &l[i], &r[i], &p[i]);
        ans += b[i] + w[i];
    }
    build();
    printf("%lld\n", ans - mxflow());
}
