// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const int M = 2e5 + 10;
const int NEKO_CNT = 2e6 + 10; // 2 * |S| + na + nb = 4e5 + 2e5 + 2e5 = 8e5
int neko_cnt;

char str[N];
int len[N], pre[N], last, cnt, ch[N][26], pos[N];

int n, fa[N][21];
vector<int> g[N];
int na, nb, m;
struct T {
    int l, r, u, len;
} rel_a[M], rel_b[M];
vector<int> lk[NEKO_CNT];
int vis[NEKO_CNT];
ll ans, f[NEKO_CNT];
vector<int> nek_A[N], nek_B[N];
int the_id[N];

int nd(int l) {
    return len[++ cnt] = l, cnt;
}
void ins(int c, int id) {
    int p, np, q, nq;
    pre[last = np = nd(len[p = last] + 1)] = 1;
    pos[id] = np;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            nq = nd(len[p] + 1);
            pre[nq] = pre[q];
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            pre[np] = pre[q] = nq;
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}

void dfs(int u) {
    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        fa[v][0] = u;
        dfs(v);
    }
}

namespace check_loop {
    stack<int> sta;
    int ins[NEKO_CNT], vis[NEKO_CNT];
    int dfs(int u) {
        if(ins[u]) {
            return 1;
        }
        if(vis[u]) {
            return 0;
        }
        ins[u] = 1, sta.push(u);
        for(int i = 0 ; i < lk[u].size() ; ++ i) {
            int v = lk[u][i];
            if(dfs(v)) {
                return 1;
            }
        }
        ins[u] = 0, sta.pop();
        vis[u] = 1;
        return 0;
    }
    int check() {
        int res = dfs(0);
        while(sta.size()) sta.pop();
        for(int i = 0 ; i <= neko_cnt ; ++ i) {
            ins[i] = vis[i] = 0;
        }
        return res;
    }
}

void go(int u) {
    if(vis[u]) {
        return ;
    }
    vis[u] = 1;
    for(int i = 0 ; i < lk[u].size() ; ++ i) {
        int v = lk[u][i];
        go(v);
        f[u] = max(f[u], f[v]);
    }
    
    if(1 <= u && u <= na) {
        f[u] += rel_a[u].len;
    }
}

int getnd(int u, int L) {
    for(int i = 20 ; ~ i ; -- i) {
        if(len[fa[u][i]] >= L) {
            u = fa[u][i];
        }
    }
    return u;
}

bool cmp_A(int x, int y) {
    return rel_a[x].len < rel_a[y].len;
}

bool cmp_B(int x, int y) {
    return rel_b[x - na].len < rel_b[y - na].len;
}

void link_edge(int u) {
    for(int i = 0 ; i < nek_B[u].size() ; ++ i) {
        int nb = nek_B[u][i];
        lk[nb].push_back(the_id[u]);
    }
    sort(nek_A[u].begin(), nek_A[u].end(), cmp_A);
    sort(nek_B[u].begin(), nek_B[u].end(), cmp_B);
    for(int i = 0 ; i < (int) nek_B[u].size() - 1 ; ++ i) {
        lk[nek_B[u][i]].push_back(nek_B[u][i + 1]);
    }

    for(int i = 0, j = -1 ; i < (int) nek_A[u].size() ; ++ i) {
        while(j + 1 < (int) nek_B[u].size() && rel_b[nek_B[u][j + 1] - na].len <= rel_a[nek_A[u][i]].len) ++ j;
        if(j >= 0) {
            lk[nek_B[u][j]].push_back(nek_A[u][i]);
        }
    }
    
    for(int i = 0 ; i < g[u].size() ; ++ i) {
        int v = g[u][i];
        lk[the_id[u]].push_back(the_id[v]);
        for(int j = 0 ; j < nek_A[v].size() ; ++ j) {
            int na = nek_A[v][j];
            lk[the_id[u]].push_back(na);
        }
        link_edge(v);
    }
}

void runprog() {
    for(int i = 0 ; i <= cnt ; ++ i) {
        the_id[i] = 0;
        nek_A[i].clear();
        nek_B[i].clear();
        memset(ch[i], 0, sizeof ch[i]);
        len[i] = pre[i] = 0;
        g[i].clear();
    }
    last = cnt = 1;
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = n ; i ; -- i) {
        ins(str[i] - 'a', i);
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        if(pre[i]) {
            g[pre[i]].push_back(i);
        }
    }
    dfs(1);
    scanf("%d", &na);
    for(int i = 1 ; i <= na ; ++ i) {
        int l, r, u; scanf("%d%d", &l, &r);
        u = pos[l];
        rel_a[i] = (T) { l, r, u, r - l + 1 };
        nek_A[getnd(u, r - l + 1)].push_back(i);
    }
    scanf("%d", &nb);
    for(int i = 1 ; i <= nb ; ++ i) {
        int l, r, u; scanf("%d%d", &l, &r);
        u = pos[l];
        rel_b[i] = (T) { l, r, u, r - l + 1 };
        nek_B[getnd(u, r - l + 1)].push_back(na + i);
    }
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        lk[u].push_back(na + v);
    }

    neko_cnt = na + nb;
    for(int i = 1 ; i <= cnt ; ++ i) {
        the_id[i] = ++ neko_cnt;
    }
    link_edge(1);
    for(int i = 1 ; i <= na ; ++ i) {
        lk[0].push_back(i);
    }
    
    if(check_loop :: check()) {
        puts("-1");
    } else {
        go(0);
        printf("%lld\n", f[0]);
        for(int i = 0 ; i <= neko_cnt ; ++ i) {
            f[i] = vis[i] = 0;
        }
    }
    
    for(int i = 0 ; i <= neko_cnt ; ++ i) {
        lk[i].clear();
    }
    neko_cnt = 0;
}

int main() {
//    auto S = clock();
//    freopen("string2.in", "r", stdin);
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
//    printf("%d\n", int(clock() - S));
}

