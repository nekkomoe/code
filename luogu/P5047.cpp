// luogu-judger-enable-o2
// luogu-judger-enable-o3
%:pragma GCC optimize(2)
%:pragma GCC optimize(3)
%:pragma GCC optimize("Ofast")
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

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
    int x = 0, c = 0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x;
}

const int N = 1e5 + 10, LEN = 450;

int n, m, a[N];

inline void lsh() {
    vector<int> num;
    for(int i = 1 ; i <= n ; ++ i) {
        num.emplace_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1;
    }
}

ll ans[N];

struct QUERY {
    int id, l, r;
} query[N];

int L[N], R[N], ids[N];

namespace WORK_1 {
    int bit[N];
    inline void add(int x, int y) {
        for( ; x <= n ; x += x & -x) {
            bit[x] += y;
        }
    }
    inline int ask(int x) {
        int r = 0;
        for( ; x ; x -= x & -x) {
            r += bit[x];
        }
        return r;
    }
    ll s[N];
    inline void runprog() {
        for(int i = 1 ; i <= n ; ++ i) {
            add(a[i], 1);
            s[i] = i - ask(a[i]);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            s[i] += s[i - 1];
        }
    }
}

namespace WORK_2 {
    int bit[N];
    inline void add(int x, int y) {
        for( ; x <= n ; x += x & -x) {
            bit[x] += y;
        }
    }
    inline int ask(int x) {
        int r = 0;
        for( ; x ; x -= x & -x) {
            r += bit[x];
        }
        return r;
    }
    ll s[N];
    inline void runprog() {
        for(int i = n ; i >= 1 ; -- i) {
            add(a[i], 1);
            s[i] = ask(a[i] - 1);
        }
        for(int i = 1 ; i <= n ; ++ i) {
            s[i] += s[i - 1];
        }
    }
}

struct T {
    int id, tag, l, r;
    T(int id, int tag, int l, int r) : id(id), tag(tag), l(l), r(r) {}
};

// [1, nek], [l, r]
vector<T> fafa_que[N];

// [l, r] [nek, n]
vector<T> haha_que[N];

namespace SOLVE_FAFA {

    int tag[N], val[N];

    inline void add(int x) {
        // [1, x - 1] ++
        for(int i = 1 ; i <= x - 1 ; ) {
            int j = R[ids[i]];
            if(j <= x - 1) {
                ++ tag[ids[i]];
            } else {
                for(int k = i ; k <= x - 1 ; ++ k) {
                    ++ val[k];
                }
            }
            i = j + 1;
        }
    }

    inline void runprog() {
        for(int i = 1 ; i <= n ; ++ i) {
            add(a[i]);
            for(T &t: fafa_que[i]) {
                for(int pos = t.l ; pos <= t.r ; ++ pos) {
                    int cnt = val[a[pos]] + tag[ids[a[pos]]];
                    ans[t.id] += t.tag * cnt;
                }
            }
        }
    }
}

namespace SOLVE_HAHA {
    
    int tag[N], val[N];

    inline void add(int x) {
        // [x + 1, n] ++

        for(int i = n ; i >= x + 1 ; ) {
            int j = L[ids[i]];
            if(j >= x + 1) {
                ++ tag[ids[i]];
            } else {
                for(int k = x + 1 ; k <= i ; ++ k) {
                    ++ val[k];
                }
            }
            i = j - 1;
        }
    }

    inline void runprog() {
        for(int i = n ; i >= 1 ; -- i) {
            add(a[i]);
            for(T &t: haha_que[i]) {
                for(int pos = t.l ; pos <= t.r ; ++ pos) {
                    int cnt = val[a[pos]] + tag[ids[a[pos]]];
                    ans[t.id] += t.tag * cnt;
                }
            }
        }
    }
}

int main() {
    n = read(), m = read();
    int LEN = sqrt(n) + 1;
    for(int i = 1 ; i <= n ; ++ i) {
        a[i] = read();
        int x = ids[i] = (i - 1) / LEN + 1;
        if(!L[x]) {
            L[x] = i;
        }
        R[x] = i;
    }
    lsh();

    for(int i = 1 ; i <= m ; ++ i) {
        query[i].l = read();
        query[i].r = read();
        query[i].id = i;
    }
    sort(query + 1, query + 1 + m, [&] (QUERY a, QUERY b) {
        return make_pair(ids[a.l], (ids[a.l] & 1 ? 1 : -1) * a.r) < make_pair(ids[b.l], (ids[b.l] & 1 ? 1 : -1) * b.r);
    });

    WORK_1 :: runprog();
    WORK_2 :: runprog();

    int l = 1, r = 0;
    for(int i = 1 ; i <= m ; ++ i) {
        int ql = query[i].l, qr = query[i].r, id = query[i].id;

        if(r < qr) {
            ans[id] += WORK_1 :: s[qr] - WORK_1 :: s[r];
            fafa_que[l - 1].emplace_back(id, -1, r + 1, qr);
            r = qr;
        }

        if(l > ql) {
            ans[id] += WORK_2 :: s[l - 1] - WORK_2 :: s[ql - 1];
            haha_que[r + 1].emplace_back(id, -1, ql, l - 1);
            l = ql;
        }

        if(r > qr) {
            ans[id] -= WORK_1 :: s[r] - WORK_1 :: s[qr];
            fafa_que[l - 1].emplace_back(id, 1, qr + 1, r);
            r = qr;
        }

        if(l < ql) {
            ans[id] -= WORK_2 :: s[ql - 1] - WORK_2 :: s[l - 1];
            haha_que[r + 1].emplace_back(id, 1, l, ql - 1);
            l = ql;
        }
    }

    SOLVE_FAFA :: runprog();
    SOLVE_HAHA :: runprog();

    for(int i = 1 ; i <= m ; ++ i) {
        ans[query[i].id] += ans[query[i - 1].id];
    }

    for(int i = 1 ; i <= m ; ++ i) {
        printf("%lld\n", ans[i]);
    }
}
