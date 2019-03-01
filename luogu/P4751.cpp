#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
%:pragma GCC optimize("Ofast")
%:pragma GCC optimize("inline")
%:pragma GCC optimize("-fgcse")
%:pragma GCC optimize("-fgcse-lm")
%:pragma GCC optimize("-fipa-sra")
%:pragma GCC optimize("-ftree-pre")
%:pragma GCC optimize("-ftree-vrp")
%:pragma GCC optimize("-fpeephole2")
%:pragma GCC optimize("-ffast-math")
%:pragma GCC optimize("-fsched-spec")
%:pragma GCC optimize("unroll-loops")
%:pragma GCC optimize("-falign-jumps")
%:pragma GCC optimize("-falign-loops")
%:pragma GCC optimize("-falign-labels")
%:pragma GCC optimize("-fdevirtualize")
%:pragma GCC optimize("-fcaller-saves")
%:pragma GCC optimize("-fcrossjumping")
%:pragma GCC optimize("-fthread-jumps")
%:pragma GCC optimize("-funroll-loops")
%:pragma GCC optimize("-fwhole-program")
%:pragma GCC optimize("-freorder-blocks")
%:pragma GCC optimize("-fschedule-insns")
%:pragma GCC optimize("inline-functions")
%:pragma GCC optimize("-ftree-tail-merge")
%:pragma GCC optimize("-fschedule-insns2")
%:pragma GCC optimize("-fstrict-aliasing")
%:pragma GCC optimize("-fstrict-overflow")
%:pragma GCC optimize("-falign-functions")
%:pragma GCC optimize("-fcse-skip-blocks")
%:pragma GCC optimize("-fcse-follow-jumps")
%:pragma GCC optimize("-fsched-interblock")
%:pragma GCC optimize("-fpartial-inlining")
%:pragma GCC optimize("no-stack-protector")
%:pragma GCC optimize("-freorder-functions")
%:pragma GCC optimize("-findirect-inlining")
%:pragma GCC optimize("-fhoist-adjacent-loads")
%:pragma GCC optimize("-frerun-cse-after-loop")
%:pragma GCC optimize("inline-small-functions")
%:pragma GCC optimize("-finline-small-functions")
%:pragma GCC optimize("-ftree-switch-conversion")
%:pragma GCC optimize("-foptimize-sibling-calls")
%:pragma GCC optimize("-fexpensive-optimizations")
%:pragma GCC optimize("-funsafe-loop-optimizations")
%:pragma GCC optimize("inline-functions-called-once")
%:pragma GCC optimize("-fdelete-null-pointer-checks")

// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;

const int BS=(1<<24)+5;char Buffer[BS],*HD,*TL;
inline char gc() { if(HD==TL) TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);return (HD==TL)?EOF:*HD++; }

char ss[30000010],tt[20];int ssl,ttl;
inline void io(int x)
{
    if(!x) ss[++ssl]='0';for(ttl=0;x;x/=10) tt[++ttl]=char(x%10+'0');
    for(;ttl;ttl--) ss[++ssl]=tt[ttl];
    ss[++ssl]='\n';
}

inline int io() {
    int x = 0, f = 0; char c = 0;
    while(!isdigit(c)) c = gc(), f |= c == '-';
    while(isdigit(c)) x = x * 10 + c - '0', c = gc();
    return f ? -x : x;
}

struct Mat {
    int a[2][2];
    Mat() { memset(a, 0xcf, sizeof a); }
    inline int* operator [] (int x) { return a[x]; }
    inline Mat operator * (Mat b) {
        Mat c;
        for(int i = 0 ; i < 2 ; ++ i) {
            for(int j = 0 ; j < 2 ; ++ j) {
                for(int k = 0 ; k < 2 ; ++ k) {
                    c[i][j] = max(c[i][j], a[i][k] +b[k][j]);
                }
            }
        }
        return c;
    }
    inline int getmx() {
        return max(max(a[0][0], a[0][1]), max(a[1][0], a[1][1]));
    }
} mat[N], neko[N];

int head[N], rest[N], to[N];
void add(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
int sz[N], son[N], n, q, lsz[N], p[N];

void dfs(int u, int fa) {
    sz[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}

int vis[N], ch[N][2], fa[N];

void upd(int u) {
    mat[u] = mat[ch[u][0]] * neko[u] * mat[ch[u][1]];
}

int isroot(int u) {
    return ch[fa[u]][0] != u && ch[fa[u]][1] != u;
}

int sta[N], top;

void getdp(int u, int v) {
    neko[u][0][0] += mat[v].getmx(), neko[u][1][0] = neko[u][0][0];
    neko[u][0][1] += max(mat[v][0][0], mat[v][1][0]);
    fa[v] = u;
}

int seq_bui(int l, int r) {
    if(l > r) return 0;
    int sum = 0;
    for(int i = l ; i <= r ; ++ i) {
        sum += lsz[sta[i]];
    }
    int cur = 0;
    for(int i = l ; i <= r ; ++ i) {
        cur += lsz[sta[i]];
        if(2 * cur >= sum) {
            fa[ch[sta[i]][0] = seq_bui(i + 1, r)] = sta[i];
            fa[ch[sta[i]][1] = seq_bui(l, i - 1)] = sta[i];
            upd(sta[i]);
            return sta[i];
        }
    }
    // assert(0);
    return -1;
}

int build(int u) {
    for(int t = u ; t ; t = son[t]) vis[t] = 1;
    for(int t = u ; t ; t = son[t]) {
        for(int i = head[t] ; i ; i = rest[i]) {
            int v = to[i];
            if(vis[v]) continue;
            getdp(t, build(v));
        }
    }
    top = 0;
    for(int t = u ; t ; t = son[t]) {
        sta[++ top] = t;
        lsz[t] = sz[t] - sz[son[t]];
    }
    return seq_bui(1, top);
}

void modify(int u, int nya) {
    neko[u][0][1] += nya - p[u], p[u] = nya;
    for( ; u ; u = fa[u]) {
        if(isroot(u) && fa[u]) {
            neko[fa[u]][0][0] -= mat[u].getmx(), neko[fa[u]][1][0] = neko[fa[u]][0][0];
            neko[fa[u]][0][1] -= max(mat[u][0][0], mat[u][1][0]);
            upd(u);
            neko[fa[u]][0][0] += mat[u].getmx(), neko[fa[u]][1][0] = neko[fa[u]][0][0];
            neko[fa[u]][0][1] += max(mat[u][0][0], mat[u][1][0]);
        } else {
            upd(u);
        }
    }
}

int main() {
    neko[0][0][0] = neko[0][1][1] = 0;
    mat[0] = neko[0];
    n = io(), q = io();
    for(int i = 1 ; i <= n ; ++ i) {
        p[i] = io();
        neko[i][0][0] = neko[i][1][0] = 0;
        neko[i][0][1] = p[i];
    }
    for(int i = 1 ; i < n ; ++ i) {
        int u = io(), v = io();
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    int root = build(1), ans = 0;
    for(int i = 1 ; i <= q ; ++ i) {
        int u = io() ^ ans, nya = io();
        modify(u, nya);
        io(ans = mat[root].getmx());
    }
    fwrite(ss+1,sizeof(char),ssl,stdout);
}

