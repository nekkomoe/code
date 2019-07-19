#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
 
const int N = 1e6 + 10;
 
int head[N], rest[N], to[N], id[N], tot, n, m, q;
void add(int u, int v, int _id) {
    to[++ tot] = v, id[tot] = _id, rest[tot] = head[u], head[u] = tot;
}
 
ll tag[N], theval[N];
ll get() {
    return (ll) rand() * rand() % int(1e9);
}
 
int vis[N], dep[N];
void dfs(int u, int fr) {
    vis[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(id[i] == fr) continue;
        if(vis[v]) {
            if(dep[v] < dep[u]) {
                ll val = get();
                tag[v] ^= val;
                tag[u] ^= val;
                theval[id[i]] = val;
            }
        } else {
            dep[v] = dep[u] + 1;
            dfs(v, id[i]);
            tag[u] ^= tag[v];
            theval[id[i]] = tag[v];
        }
    }
}
 
ll a[N];

struct FastIO {
    static const int S = 2e6;
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
 
int main() {
    srand(34098233);
    n = io(), m = io();
    for(int i = 1, u, v ; i <= m ; ++ i) {
        u = io(), v = io();
        add(u, v, i), add(v, u, i);
    }
    dep[1] = 0;
    dfs(1, 0);
    q = io();
    ll lastans = 0;
    while(q --) {
        int k = io();
        k ^= lastans;
        vector<int> rd;
        while(k --) {
            int x = io();
            x ^= lastans;
            rd.push_back(x);
        }
        sort(rd.begin(), rd.end());
        rd.erase(unique(rd.begin(), rd.end()), rd.end());
        for(int i = 0 ; i <= 60 ; ++ i) a[i] = 0;
        int val = 1;
        for(int i = 0 ; i < rd.size() ; ++ i) {
            ll x = theval[rd[i]];
            for(int j = 60 ; ~ j ; -- j) {
                if(x & (1ll << j)) {
                    if(!a[j]) {
                        a[j] = x;
                        break;
                    } else {
                        x ^= a[j];
                    }
                }
            }
            if(x == 0) {
                val = 0;
                break;
            }
        }
        lastans += val;
        puts(val ? "Connected" : "Disconnected");
    }
}
