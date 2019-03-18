#pragma GCC optimize(2)
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
using namespace std;
typedef long long ll;

const int N = 4e5 + 10;
const int LEN = 1000;

priority_queue<int> pq[N]; // 维护最大值
priority_queue<int, vector<int>, greater<int> > tag[N]; // 维护标记，显然跟顺序无关

int n, q, L[N], R[N], cnt, a[N], bel[N];

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
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

void getpq(int x) {
    pq[x] = priority_queue<int> ();
    for(int i = L[x] ; i <= R[x] ; ++ i) {
        pq[x].push(a[i]);
    }
}

void push(int x) {
    if(tag[x].size()) {
        for(int i = L[x] ; i <= R[x] ; ++ i) {
            int y = tag[x].top(); tag[x].pop();
            if(y < a[i]) swap(a[i], y);
            tag[x].push(y);
        }
        tag[x] = priority_queue<int, vector<int>, greater<int> > ();
    }
}

// 模拟题意即可
int get(int l, int r, int x) {
    if(bel[l] == bel[r]) {
        push(bel[l]);
        for(int i = l ; i <= r ; ++ i) {
            if(x < a[i]) {
                swap(x, a[i]);
            }
        }
        getpq(bel[l]);
        return x;
    } else {
        x = get(l, R[bel[l]], x);
        for(int i = bel[l] + 1 ; i <= bel[r] - 1 ; ++ i) {
            if(pq[i].top() > x) {
                int y = pq[i].top(); pq[i].pop();
                tag[i].push(x);
                pq[i].push(x);
                x = y;
            }
        }
        return get(L[bel[r]], r, x);
    }
}

void runprog() {
    int l = io(), r = io(), x = io();
    if(l <= r) {
        io(get(l, r, x));
    } else {
        io(get(1, r, get(l, n, x)));
    }
}

int main() {
    // cout << sqrt(N) << endl;    
    n = io(), q = io();
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = io();
        int x = bel[i] = (i - 1) / LEN + 1;
        L[x] = L[x] ? L[x] : i;
        R[x] = i;
    }
    cnt = bel[n];
    for(int i = 1 ; i <= cnt ; ++ i) {
        getpq(i);
    }
    while(q --) {
        runprog();
    }
}
