#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct FastIO {
    static const int S = 1e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline ll operator ! () {
        int c = xchar(); ll x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline void wchar(int x) {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void operator () (ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void space(ll x) {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar(' ');
    }
    inline void nextline() {
        wchar('\n');
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

const int N = 10010 + 10;

int n, dep[N], fa[N][22];
vector<int> g[N];
void dfs(int u) {
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = 1 ; i <= 20 ; ++ i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for(int v: g[u]) {
        if(v != fa[u][0]) {
            fa[v][0] = u;
            dfs(v);
        }
    }
}
int getlca(int u, int v) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 20 ; ~ i ; -- i) {
        if(dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = 20 ; ~ i ; -- i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}

int inchain_sub(int x, int u, int v) {
    return getlca(x, u) == x && getlca(x, v) == v;
}

int inchain(int x, int u, int v) {
    int w = getlca(u, v);
    assert(w);
    return inchain_sub(x, u, w) || inchain_sub(x, v, w);
}

void runprog() {
    static int T = 0;
    printf("Case %d:\n", ++ T);
    n = io();
    for(int i = 1 ; i <= n ; ++ i) {
        g[i].clear();
    }
    for(int i = 1, u, v ; i < n ; ++ i) {
        u = io(), v = io();
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1);
    int q = io();
    while(q --) {
        int k = io();
        int a = -1, b = -1;
        while(k --) {
            int u = io(), v = io();
            if(a == -2) {
                continue;
            } else if(a == -1) {
                a = u, b = v;
            } else {
                int lab = getlca(a, b);
                int luv = getlca(u, v);

                assert(lab && luv);

                vector<int> p, q;
                p.emplace_back(a);
                p.emplace_back(b);
                p.emplace_back(u);
                p.emplace_back(v);
                for(int i = 0 ; i < 4 ; ++ i) {
                    for(int j = 0 ; j < 4 ; ++ j) {
                        p.emplace_back(getlca(p[i], p[j]));
                    }
                }
                sort(p.begin(), p.end());
                p.erase(unique(p.begin(), p.end()), p.end());
                for(int x: p) {
                    if(inchain(x, u, v) && inchain(x, a, b)) {
                        q.emplace_back(x);
                    }
                }


                if(q.empty()) {
                    a = -2;
                } else {
                    int mx = -1;
                    for(int x: q) {
                        for(int y: q) {
                            int len = dep[x] + dep[y] - 2 * dep[getlca(x, y)] + 1;
                            if(len >= mx) {
                                a = x, b = y;
                                mx = len;
                            }
                        }
                    }
                }
            }
            // printf("(%d, %d)\n", a, b);
        }
        if(a < 0) puts("0");
        else printf("%d\n", dep[a] + dep[b] - 2 * dep[getlca(a, b)] + 1);
    }
}

int main() {
    int t = io();
    while(t --) {
        runprog();
    }
}
