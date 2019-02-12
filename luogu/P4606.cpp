#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n, m, q, head[N], rest[N], to[N], tot, cnt, isCir[N], sum[N];

int sta[N], top, dfn[N], low[N], clk;

int dfn_pri[N], dfn_end[N], dfn_clk, fa[N][25], dep[N], ele[N], ele_top;

vector<int> g[N];

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

void lk(int u, int v) {

    // printf("%d <---> %d\n", u, v);

    g[u].push_back(v);
    g[v].push_back(u);
}

void tarj(int u, int fa) {
    dfn[u] = low[u] = ++ clk;
    sta[++ top] = u;
    isCir[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            tarj(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                ++ cnt;
                lk(u, cnt);
                int tmp;
                do {
                    tmp = sta[top --];
                    lk(cnt, tmp);
                } while(tmp != v);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void getsum(int u, int fa) {
    dep[u] = dep[fa] + 1;
    :: fa[u][0] = fa;
    for(int i = 1 ; i <= 20 ; ++ i) {
        :: fa[u][i] = :: fa[:: fa[u][i - 1]][i - 1];
    }
    dfn_pri[u] = ++ dfn_clk;
    sum[u] = isCir[u] + sum[fa];
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        if(v == fa) continue;
        getsum(v, u);
    }
    dfn_end[u] = dfn_clk;
}

int getlca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int cmp(int a, int b) {
    return dfn_pri[a] < dfn_pri[b];
}

int ask() {
    int rem = ele_top;
    sort(ele + 1, ele + 1 + ele_top, cmp);
    for(int i = ele_top ; i >= 2 ; -- i) {
        ele[++ ele_top] = getlca(ele[i], ele[i - 1]);
    }
    sort(ele + 1, ele + 1 + ele_top, cmp);
    ele_top = unique(ele + 1, ele + 1 + ele_top) - ele - 1;
    
    // for(int i = 1 ; i <= ele_top ; ++ i) {
    //     printf("%d ", ele[i]);
    // }
    // puts("");

    int res = 0;
    res += isCir[ele[1]];
    top = 0;
    for(int i = 1 ; i <= ele_top ; ++ i) {
        int u = ele[i];
        while(top && dfn_end[sta[top]] < dfn_pri[u]) -- top;
        if(top) {
            int fa = sta[top];
            // fa -> u
            res += sum[u] - sum[fa];
            // printf("%d -> %d, delta = %d\n", fa, u, sum[u] - sum[fa]);
        }
        sta[++ top] = u;
    }
    return res - rem;
}

void clear_fafa() {
// int n, m, q, head[N], rest[N], to[N], tot, cnt, isCir[N], sum[N];

// int sta[N], top, dfn[N], low[N], clk;

// int dfn_pri[N], dfn_end[N], dfn_clk, fa[N][25], dep[N], ele[N], ele_top;

// vector<int> g[N];
    
    tot = top = clk = dfn_clk = 0;
    for(int i = 1 ; i <= cnt ; ++ i) {
        head[i] = 0;
        g[i].clear();
        dfn[i] = 0;
        isCir[i] = 0;
        sum[i] = 0;
    }
}

void runprog() {
    scanf("%d%d", &n, &m);
    cnt = n;
    while(m --) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    tarj(1, 0);
    getsum(1, 0);

    // for(int i = 1 ; i <= cnt ; ++ i) {
    //     printf("sum[%d] = %d\n", i, sum[i]);
    // }

    scanf("%d", &q);
    while(q --) {
        scanf("%d", &ele_top);
        for(int i = 1 ; i <= ele_top ; ++ i) {
            scanf("%d", &ele[i]);
        }
        printf("%d\n", ask());
    }

    // clear
    clear_fafa();
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
