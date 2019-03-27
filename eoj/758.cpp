#pragma GCC optimize(2)
#pragma GCC target("popcnt")
#include "bits/stdc++.h"
using namespace std;

const int N = 3e5 + 10;

int n, m, a[N], deg[N], px[N], py[N];
int ch[N][3];

int dfn1[N], dfn2[N], clk1, clk2;
int vis1[N], vis2[N];
void dfs1(int u) {
    if(!u || vis1[u]) return ;
    vis1[u] = 1;
    dfs1(ch[u][1]);
    dfs1(ch[u][2]);
    dfn1[u] = ++ clk1;
}

void dfs2(int u) {
    if(!u || vis2[u]) return ;
    vis2[u] = 1;
    dfs2(ch[u][2]);
    dfs2(ch[u][1]);
    dfn2[u] = ++ clk2;
}
int p[N];
int bit[N];
void add(int x, int y) {
    for( ; x <= n ; x += x & -x) {
        bit[x] += y;
    }
}

int ask(int x) {
    int res = 0;
    for( ; x ; x -= x & -x) {
        res += bit[x];
    }
    return res;
}
int mnpos[N], ans[N];
map<int, int> tra; int tot;

int main() {
//    freopen("souvenir.in", "r", stdin);
//    freopen("souvenir.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d%d%d", &px[i], &py[i], &a[i]);
        if(tra.count(a[i])) a[i] = tra[a[i]];
        else a[i] = tra[a[i]] = ++ tot;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        if((px[u] == px[v] && py[u] > py[v])
        || (py[u] == py[v] && px[u] > px[v])) swap(u, v);
        if(px[u] == px[v]) ch[u][1] = v; // y
        if(py[u] == py[v]) ch[u][2] = v; // x
    }
    dfs1(1);
    dfs2(1);

    for(int i = 1 ; i <= n ; ++ i) p[i] = i, mnpos[i] = 0x3f3f3f3f;
    sort(p + 1, p + 1 + n, [&] (int a, int b) { return dfn1[a] < dfn1[b]; });

    for(int i = 1 ; i <= n ; ++ i) {
        int u = p[i];
        if(dfn2[u] < mnpos[a[u]]) {
            add(mnpos[a[u]], -1);
            mnpos[a[u]] = dfn2[u];
            add(mnpos[a[u]], 1);
        }
        ans[u] = ask(dfn2[u]);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
