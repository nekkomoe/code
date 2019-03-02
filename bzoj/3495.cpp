#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 4e6 + 10;

int n, m, k;
int head[N], rest[N * 2], to[N * 2], tot;

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

void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int dfn[N], low[N], clk, ins[N], id[N], cnt;

stack<int> s;

void dfs(int u) {
    dfn[u] = low[u] = ++ clk;
    s.push(u);
    ins[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int  v = to[i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        cnt ++;
        int v;
        do {
            v = s.top();
            s.pop();
            ins[v] = 0;
            id[v] = cnt;
        } while(u != v);
    }
}

int main() {
    n = io(), m = io(), k = io();
    for(int i = 1 ; i <= n ; ++ i) {
        add(i, 2 * n + i);
        add(3 * n + i, i + n);
    }
    for(int i = 1, u, v ; i <= m ; ++ i) {
        u = io(), v = io();
        add(u + n, v);
        add(v + n, u);
    }
    for(int i = 1 ; i <= k ; ++ i) {
        int num = io(), last = io(), cur;
        for(int j = 2 ; j <= num ; ++ j, last = cur) {
            cur = io();
            add(2 * n + last, 2 * n + cur);
            add(3 * n + cur, 3 * n + last);
            add(cur, 3 * n + last);
            add(2 * n + last, cur + n);
        }
    }
    for(int i = 1 ; i <= n * 4 ; ++ i) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if(id[i] == id[i + n]) {
            puts("NIE");
            return 0;
        }
    }
    for(int i = 2 * n + 1 ; i <= 3 * n ; ++ i) {
        if(id[i] == id[i + n]) {
            puts("NIE");
            return 0;
        }
    }
    puts("TAK");
}
