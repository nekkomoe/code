// 1. k个点到它们的lca都求一遍
#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;

int a[N], head[N], rest[N], to[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sum[N * 31], lc[N * 31], rc[N * 31], root[N];

int nd() {
    static int tot = 0;
    return ++ tot;
}

void modify(int last, int now, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    sum[now] = sum[last] + 1;
    lc[now] = lc[last], rc[now] = rc[last];
    if(l == r) return ;
    if(pos <= mid) modify(lc[last], lc[now] = nd(), l, mid, pos);
    else modify(rc[last], rc[now] = nd(), mid + 1, r, pos);
}

int dfn[N], fa[N][21], dep[N];

void dfs(int u) {
    static int tot = 0;
    modify(root[fa[u][0]], root[u] = nd(), 1, int(1e9), a[u]);
    dfn[u] = ++ tot;
    for(int i = 1 ; i <= 20 ; ++ i)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u][0]) continue;
        fa[v][0] = u;
        dfs(v);
    }
}

int pre(int L, int R, int l, int r, int val) {
    int mid = (l + r) >> 1;
    if(sum[R] - sum[L] == 0) return -1;
    else if(l > val) return -1;
    else if(l == r) {
        if(sum[R] - sum[L]) return l;
        else return -1;
    } else {
        int tr = pre(rc[L], rc[R], mid + 1, r, val);
        if(tr != -1) {
            return tr;
        } else {
            return pre(lc[L], lc[R], l, mid, val);
        }
    }
}

int sub(int L, int R, int l, int r, int val) {
    int mid = (l + r) >> 1;
    if(sum[R] - sum[L] == 0) return -1;
    else if(r < val) return -1;
    else if(l == r) {
        if(sum[R] - sum[L]) return l;
        else return -1;
    } else {
        int tl = sub(lc[L], lc[R], l, mid, val);
        if(tl != -1) {
            return tl;
        } else {
            return sub(rc[L], rc[R], mid + 1, r, val);
        }
    }
}

int n, q, type, lastans, p[N];

bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int query(int val, int u, int v) {
    int PRE = pre(root[fa[u][0]], root[v], 1, int(1e9), val);
    int SUB = sub(root[fa[u][0]], root[v], 1, int(1e9), val);
    if(PRE != -1 && SUB != -1) return min(abs(val - PRE), abs(val - SUB));
    if(PRE == -1 && SUB == -1) return int(1e9);
    if(PRE == -1) swap(PRE, SUB); return abs(val - PRE);
}

int sol(int val, int k) {
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%d", &p[i]);
        if(type) p[i] = (p[i] - 1 + lastans) % n + 1;
    }
    int mn = p[1], mx = p[1];
    for(int i = 1 ; i <= k ; ++ i) {
        if(dfn[p[i]] < dfn[mn]) mn = p[i];
        if(dfn[p[i]] > dfn[mx]) mx = p[i];
    }
    int lca = getlca(mn, mx);
    int ans = 1e9;
    for(int i = 1 ; i <= k ; ++ i)
        ans = min(ans, query(val, lca, p[i]));
    return ans;
}

int main() {
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    scanf("%d%d%d", &n, &q, &type);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    for(int i = 1, val, k ; i <= q ; ++ i) {
        scanf("%d%d", &val, &k);
        printf("%d\n", lastans = sol(val, k));
    }
}

// 2. 大力造虚树
#include "bits/stdc++.h"
using namespace std;
const int N = 2e5 + 10;

int a[N], head[N], rest[N], to[N];

void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int sum[N * 31], lc[N * 31], rc[N * 31], root[N];

int nd() {
    static int tot = 0;
    return ++ tot;
}

void modify(int last, int now, int l, int r, int pos) {
    int mid = (l + r) >> 1;
    sum[now] = sum[last] + 1;
    lc[now] = lc[last], rc[now] = rc[last];
    if(l == r) return ;
    if(pos <= mid) modify(lc[last], lc[now] = nd(), l, mid, pos);
    else modify(rc[last], rc[now] = nd(), mid + 1, r, pos);
}

int dfn[N], l[N], r[N], fa[N][21], dep[N];

void dfs(int u) {
    static int tot = 0;
    modify(root[fa[u][0]], root[u] = nd(), 1, int(1e9), a[u]);
    dfn[u] = ++ tot, l[u] = tot;
    for(int i = 1 ; i <= 20 ; ++ i)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa[u][0]) continue;
        fa[v][0] = u;
        dfs(v);
    }
    r[u] = tot;
}

int pre(int L, int R, int l, int r, int val) {
    int mid = (l + r) >> 1;
    if(sum[R] - sum[L] == 0) return -1;
    else if(l > val) return -1;
    else if(l == r) {
        if(sum[R] - sum[L]) return l;
        else return -1;
    } else {
        int tr = pre(rc[L], rc[R], mid + 1, r, val);
        if(tr != -1) {
            return tr;
        } else {
            return pre(lc[L], lc[R], l, mid, val);
        }
    }
}

int sub(int L, int R, int l, int r, int val) {
    int mid = (l + r) >> 1;
    if(sum[R] - sum[L] == 0) return -1;
    else if(r < val) return -1;
    else if(l == r) {
        if(sum[R] - sum[L]) return l;
        else return -1;
    } else {
        int tl = sub(lc[L], lc[R], l, mid, val);
        if(tl != -1) {
            return tl;
        } else {
            return sub(rc[L], rc[R], mid + 1, r, val);
        }
    }
}

int n, q, type, lastans, p[N];

bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int query(int val, int u, int v) {
    int PRE = pre(root[fa[u][0]], root[v], 1, int(1e9), val);
    int SUB = sub(root[fa[u][0]], root[v], 1, int(1e9), val);
    if(PRE != -1 && SUB != -1) return min(abs(val - PRE), abs(val - SUB));
    if(PRE == -1 && SUB == -1) return int(1e9);
    if(PRE == -1) swap(PRE, SUB); return abs(val - PRE);
}

int sol(int val, int k) {
    for(int i = 1 ; i <= k ; ++ i) {
        scanf("%d", &p[i]);
        p[i] = (p[i] - 1 + lastans * type) % n + 1;
    }
    sort(p + 1, p + 1 + k, cmp);
    for(int i = k ; i >= 2 ; -- i) {
        p[++ k] = getlca(p[i], p[i - 1]);
    }
    sort(p + 1, p + 1 + k, cmp);
    k = unique(p + 1, p + 1 + k) - p - 1;
    stack<int> s;
    int ans = 1e9;
    for(int i = 1 ; i <= k ; ++ i) {
        int v = p[i];
        if(s.empty()) {
            s.push(v);
            ans = min(ans, abs(a[v] - val));
        } else {
            int u = s.top();
            while(s.size() && r[u] < l[v]) {
                s.pop();
                if(s.size()) u = s.top();
            }
            if(s.size()) {
                ans = min(ans, query(val, u, v));
            }
            s.push(v);
        }
    }
    return ans;
}

int main() {
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    scanf("%d%d%d", &n, &q, &type);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &a[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1);
    for(int i = 1, val, k ; i <= q ; ++ i) {
        scanf("%d%d", &val, &k);
        printf("%d\n", lastans = sol(val, k));
    }
}
