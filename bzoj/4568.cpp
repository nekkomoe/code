%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 20000 + 10;

ll val[N];

struct BAS { ll val[62]; } bas[N][20], la;

int n, q, fa[N][20], deep[N], head[N], rest[N * 2], to[N * 2];

template<typename T> inline void read(T &x) {
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

inline void add(int u, int v) { static int tot = 0; to[++ tot] = v, rest[tot] = head[u], head[u] = tot; }

inline int getlca(int u, int v) {
    if(deep[u] < deep[v]) swap(u, v);
    for(int i = 15 ; ~ i ; -- i) if(deep[fa[u][i]] >= deep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 15 ; ~ i ; -- i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

inline void ins(BAS &bas, ll val) {
    for(int i = 60 ; ~ i ; -- i) {
        if((val >> i) & 1) {
            if(!bas.val[i]) {
                bas.val[i] = val;
                break;
            }
            val ^= bas.val[i];
        }
    }
}

inline void merge(BAS &bas, BAS &src) { for(int i = 60 ; ~ i ; -- i) if(src.val[i]) ins(bas, src.val[i]); }

inline ll query(BAS &bas) {
    ll res = 0;
    for(int i = 60 ; ~ i ; -- i)
        if((res ^ bas.val[i]) > res) res ^= bas.val[i];
    return res;
}

void dfs(int u) {
    deep[u] = deep[fa[u][0]] + 1;
    ins(bas[u][0], val[u]);
    for(int i = 1 ; i <= 15 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        merge(bas[u][i], bas[u][i - 1]), merge(bas[u][i], bas[fa[u][i - 1]][i - 1]);
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u][0]) fa[v][0] = u, dfs(v);
    }
}

inline ll sol(int u, int v) {
    memset(la.val, 0, sizeof la.val);
    int d = getlca(u, v);
    if(u == v) {
        ins(la, val[u]);
    } else if(d == u || d == v) {
        if(deep[u] > deep[v]) swap(u, v);
        for(int i = 15 ; ~ i ; -- i)
            if(deep[fa[v][i]] >= deep[u]) merge(la, bas[v][i]), v = fa[v][i];
        ins(la, val[u]);
    } else {
        for(int i = 15 ; ~ i ; -- i) {
            if(deep[fa[u][i]] >= deep[d]) merge(la, bas[u][i]), u = fa[u][i];
            if(deep[fa[v][i]] >= deep[d]) merge(la, bas[v][i]), v = fa[v][i];
        }
        ins(la, val[d]);
    }
    return query(la);
}

int main() {
    read(n), read(q);
    for(int i = 1 ; i <= n ; ++ i) read(val[i]);
    for(int i = 1, u, v ; i < n ; ++ i) {
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dfs(1);
    for(int i = 1, u, v ; i <= q ; ++ i) {
        read(u), read(v);
        printf("%lld\n", sol(u, v));
    }
}
