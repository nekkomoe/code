#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
 
using namespace std;
 
const int N = 500010;
 
int head[N], rest[N * 2], to[N * 2], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int fa[N][21], deep[N], l[N], r[N], cnt;
 
void dfs(int u) {
    u[l] = ++ cnt;
    u[deep] = u[fa][0][deep] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != u[fa][0]) {
            v[fa][0] = u;
            dfs(v);
        }
    }
    u[r] = cnt;
}
 
int lca(int u, int v) {
    if(u[deep] < v[deep]) swap(u, v);
    for(int i = 20 ; i >= 0 ; -- i) {
        if(u[fa][i][deep] >= v[deep]) {
            u = u[fa][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; i >= 0 ; -- i) {
        if(u[fa][i] != v[fa][i]) {
            u = u[fa][i];
            v = v[fa][i];
        }
    }
    return u[fa][0];
}
 
int n, m;
 
int val[N], bit[N];
 
void modify(int i, int v) {
    while(i <= n) {
        bit[i] ^= v;
        i += i & -i;
    }
}
 
int query(int i) {
    int ret = 0;
    while(i) {
        ret ^= bit[i];
        i -= i & -i;
    }
    return ret;
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d", &val[i]);
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1);
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int u = 1 ; u <= n ; ++ u) {
            u[fa][j] = u[fa][j - 1][fa][j - 1];
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        modify(i[l], i[val]);
        modify(i[r] + 1, i[val]);
    }
    scanf("%d", &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        char op[5];
        scanf("%s%d%d", op, &u, &v);
        if(op[0] == 'Q') {
            if(query(u[l]) ^ query(v[l]) ^ val[lca(u, v)]) {
                puts("Yes");
            } else {
                puts("No");
            }
        } else {
            modify(u[l], u[val]), modify(u[r] + 1, u[val]);
            u[val] = v;
            modify(u[l], u[val]), modify(u[r] + 1, u[val]);
        }
    }
    return 0;
}
