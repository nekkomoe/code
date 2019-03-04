#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 4e5 + 10;

char s[N];
int p, q, np, nq, ch[N][26], last = 1, cnt = 1, pre[N], len[N], pos[N], n, Q;
int nd(int l) { return len[++ cnt] = l, cnt; }
void ins(int c, int i) {
    pre[last = np = nd(len[p = last] + 1)] = 1;
    pos[i] = np;
    while(p && !ch[p][c]) ch[p][c] = np, p = pre[p];
    if(p) {
        pre[np] = q = ch[p][c];
        if(len[p] + 1 != len[q]) {
            pre[nq = nd(len[p] + 1)] = pre[q], pre[q] = pre[np] = nq;
            memcpy(ch[nq], ch[q], sizeof ch[q]);
            while(p && ch[p][c] == q) ch[p][c] = nq, p = pre[p];
        }
    }
}
vector<int> g[N]; int fa[N][22], dep[N];
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
int dfn[N], dfnend[N], clk;
void dfs(int u) {
    dfn[u] = ++ clk;
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int v: g[u]) {
        fa[v][0] = u;
        dfs(v);
    }
    dfnend[u] = clk;
}
void init() {
    for(int i = 1 ; i <= n ; ++ i) ins(s[i] - 'a', n - i + 1);
    for(int i = 1 ; i <= cnt ; ++ i) {
        g[pre[i]].push_back(i);
    }
    dfs(1);
}

int a[N], b[N], acnt, bcnt;
ll ans;

int tag[N]; // 0: 无, 1: a, 2: b
int seq[N], seqcnt;

vector<int> to[N];
int sta[N], top;
bool cmp(int a, int b) {
    return dfn[a] < dfn[b];
}

ll f[N][2];

void go(int u) {
    f[u][0] = !!(tag[u] & 1);
    f[u][1] = !!(tag[u] & 2);
    ll res = f[u][0] * f[u][1];
    for(int v: to[u]) {
        go(v);
        res += f[v][0] * f[u][1] + f[v][1] * f[u][0];
        f[u][0] += f[v][0];
        f[u][1] += f[v][1];
    }
    ans += res * len[u];
}

void nenene() {
    for(int i = 1 ; i <= acnt ; ++ i) {
        tag[a[i]] |= 1;
        seq[++ seqcnt] = a[i];
    }
    for(int i = 1 ; i <= bcnt ; ++ i) {
        tag[b[i]] |= 2;
        seq[++ seqcnt] = b[i];
    }

    sort(seq + 1, seq + 1 + seqcnt, cmp);
    seqcnt = unique(seq + 1, seq + 1 + seqcnt) - seq - 1;
    for(int i = seqcnt ; i >= 2 ; -- i) {
        seq[++ seqcnt] = getlca(seq[i], seq[i - 1]);
    }
    sort(seq + 1, seq + 1 + seqcnt, cmp);
    seqcnt = unique(seq + 1, seq + 1 + seqcnt) - seq - 1;

    top = 0;
    for(int i = 1 ; i <= seqcnt ; ++ i) {
        int u = seq[i];
        while(top && dfnend[sta[top]] < dfn[u]) {
            -- top;
        }
        if(top) {
            to[sta[top]].push_back(u);
            // printf("%d -> %d\n", sta[top], u);
        }
        sta[++ top] = u;
    }

    go(sta[1]);

    // cout << len[1] << ' ' << len[7] << ' ' << len[8] << endl;
    // exit(0);


    for(int i = 1 ; i <= seqcnt ; ++ i) {
        tag[seq[i]] = 0;
        to[seq[i]].clear();
    }
    seqcnt = 0;
}

void runprog() {
    scanf("%d%d", &acnt, &bcnt);
    for(int i = 1 ; i <= acnt ; ++ i) {
        scanf("%d", &a[i]);
        a[i] = pos[a[i]];
    }
    for(int i = 1 ; i <= bcnt ; ++ i) {
        scanf("%d", &b[i]);
        b[i] = pos[b[i]];
    }

    ans = 0;
    // for(int i = 1 ; i <= acnt ; ++ i) {
    //     for(int j = 1 ; j <= bcnt ; ++ j) {
    //         ans += len[getlca(a[i], b[j])];
    //     }
    // }
    nenene();
    printf("%lld\n", ans);
}

int main() {
    scanf("%d%d%s", &n, &Q, s + 1);
    reverse(s + 1, s + 1 + n);
    init();
    while(Q --) {
        runprog();
    }
}
