#pragma GCC optimize(2)
// #pragma GCC optimize(3)
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

#include "bits/stdc++.h"
typedef long long ll;
using namespace std;

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
        // if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int operator () () {
        int c = 0, x = 0, f = 0;
        while(!isdigit(c)) {
            c = xchar();
            if(c == '-') {
                f = 1;
            }
        }
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return f ? -x : x;
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

const int N = 1e6 + 10;
const ll deinf = 0xcfcfcfcfcfcfcfcfll;

int n;
ll a[N];
int rev[N], lim;

void getrev() {
    // 获得每个a[i]的离散化的值
    vector<int> num;
    for(int i = 0 ; i <= n ; ++ i) {
        num.push_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    lim = num.size();
    for(int i = 0 ; i <= n ; ++ i) {
        rev[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
    }
}

#define lc (id << 1)
#define rc (id << 1 | 1)
struct P {
    ll x, y;
} pts[N];
P operator - (P a, P b) {
    return (P) { a.x - b.x, a.y - b.y };
}
// 不用__int128真的不会爆吗……
ll operator * (P a, P b) {
    return (ll) a.x * b.y - (ll) b.x * a.y;
}

const int T = 2e7 + 10;
int nxt[T], lst[T], val[T], tot;
int _front[N], _back[N];

inline int pop_back(int id) {

    if(_front[id] == _back[id]) {
        int res = _front[id];
        nxt[res] = lst[res] = 0;
        _front[id] = _back[id] = 0;
        return res;
    }

    int res = _back[id];
    _back[id] = lst[_back[id]];
    nxt[_back[id]] = 0;
    nxt[res] = lst[res] = 0;
    return res;    
}

inline void push_back(int id, int nek) {

    lst[nek] = nxt[nek] = 0;

    if(!_front[id]) {
        _front[id] = _back[id] = nek;
        return ;
    }

    nxt[_back[id]] = nek;
    lst[nek] = _back[id];
    _back[id] = nek;
}

inline int pop_front(int id) {

    if(_front[id] == _back[id]) {
        int res = _front[id];
        nxt[res] = lst[res] = 0;
        _front[id] = _back[id] = 0;
        return res;
    }

    int res = _front[id];
    _front[id] = nxt[_front[id]];
    lst[_front[id]] = 0;
    nxt[res] = lst[res] = 0;
    return res;
}

inline void push_front(int id, int nek) {

    lst[nek] = nxt[nek] = 0;

    if(!_front[id]) {
        _front[id] = _back[id] = nek;
        return ;
    }

    lst[_front[id]] = nek;
    nxt[nek] = _front[id];
    _front[id] = nek;
}

inline void tb_ins(int id, int w) {
    while(_front[id] != _back[id]) {
        int t = pop_back(id);
        int v = val[t];
        int u = val[_back[id]];
        // u v w
        if((pts[w] - pts[v]) * (pts[u] - pts[v]) >= 0) {
            // pass
        } else {
            push_back(id, t);
            break;
        }
    }
    val[++ tot] = w;
    push_back(id, tot);
}

ll tb_ask(int id, ll k) {
    k = -k;

    ll res = deinf;
    while(_front[id] != _back[id]) {
        int t = pop_front(id);
        int u = val[t];
        int v = val[_front[id]];
        if((pts[v].y - pts[u].y) >= k * (pts[v].x - pts[u].x)) {
            // pass
        } else {
            push_front(id, t);
            break;
        }
    }
    if(_front[id]) {
        int p = val[_front[id]];
        res = max(res, pts[p].y - pts[p].x * k);
    }
    return res;
}

void modify(int x, int y) {
    for( ; x <= lim ; x += x & -x) {
        tb_ins(x, y);
    }
}

ll ask(int x, ll k) {
    ll res = deinf;
    for( ; x ; x -= x & -x) {
        res = max(res, tb_ask(x, k));
    }
    return res;
}

ll calcY(ll x, ll f) {
    return f - x * (x + 1) / 2;
}

ll cost(ll l, ll r) {
    // 在[l,r]都没有选择的情况下，端点[l,r]的代价和
    return (ll) (l + r) * (r - l + 1) / 2 + (ll) (r - l + 1) * (1 - l);
}

int main() {
    n = io();
    a[0] = -1e9 - 10;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
    }
    getrev();
    ll ans = -cost(1, n);
    pts[0] = (P) { 0, calcY(0, 0) };
    modify(rev[0], 0);
    for(int i = 1 ; i <= n ; ++ i) {
        ll f = ask(rev[i], i) + a[i] + (ll) i * (1 - i) / 2;
        pts[i] = (P) { i, calcY(i, f) };
        modify(rev[i], i);
        ans = max(ans, f - cost(i + 1, n));
    }
    io(ans);
}
