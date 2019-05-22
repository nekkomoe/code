// luogu-judger-enable-o2
#include "bits/stdc++.h"
using namespace std;
const int N = 4e5 + 10;
typedef long long ll;
int n, q;
char str[2 * N], bak[2 * N];
int rig[2 * N];
int R[N], R_pri[N];

void run_manacher() {
    for(int i = n ; i ; -- i) {
        str[2 * i] = str[i];
    }
    for(int i = 1 ; i <= 2 * n + 1 ; i += 2) {
        str[i] = '#';
    }
    n = 2 * n + 1;
    for(int i = 1, pos = -1, mxr = -1 ; i <= n ; ++ i) {
        rig[i] = i > mxr ? 1 : min(mxr - i, rig[2 * pos - i]);
        while(i - rig[i] >= 1 && i + rig[i] <= n && str[i - rig[i]] == str[i + rig[i]]) ++ rig[i];
        if(i + rig[i] - 1 > mxr) {
            mxr = i + rig[i] - 1;
            pos = i;
        }
    }

    for(int i = 1, j = 0 ; i <= n ; ++ i) {
        if(str[i] != '#') {
            R[++ j] = rig[i] / 2 - 1;
        } else {
            if(j) {
                R_pri[j] = (rig[i] - 1) / 2 - 1;
            }
        }
    }
}

const int base = 233;
typedef unsigned long long ull;
ull hs[2 * N], pw[2 * N];

ull geths(ull l, ull r) {
    return hs[r] - hs[l - 1] * pw[r - l + 1];
}

int getlcs(int x, int y) {
    if(bak[x] != bak[y]) {
        return 0;
    }
    int res = 0;
    int l = 1, r = min(x, y);
    while(l <= r) {
        int mid = (l + r) >> 1;
        // [x - mid + 1, x]
        // [y - mid + 1, y]
        if(geths(x - mid + 1, x) == geths(y - mid + 1, y)) {
            l = mid + 1;
            res = mid;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

void build_sam() {
    pw[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        pw[i] = pw[i - 1] * base;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        hs[i] = hs[i - 1] * base + (str[i] - 'a');
    }
}

#define N (7555555 * 2)
// #define N (8582200)
int lc[N], rc[N], nek_cnt, mn[N];
#undef N
// 实际上可以先跑前一半，然后再跑后一般，懒得改了

struct NEK_TREE {
    int rt[N];
    void modify(int lst, int x, int l, int r, int pos) {
        int mid = (l + r) >> 1;
        lc[x] = lc[lst], rc[x] = rc[lst], mn[x] = mn[lst];
        if(l == r) {
            mn[x] = pos;
            return ;
        } else if(pos <= mid) {
            modify(lc[lst], lc[x] = ++ nek_cnt, l, mid, pos);
            mn[x] = min(mn[x], mn[lc[x]]);
        } else {
            modify(rc[lst], rc[x] = ++ nek_cnt, mid + 1, r, pos);
            mn[x] = min(mn[x], mn[rc[x]]);
        }
    }
    int ask(int x, int l, int r, int ql, int qr) {
        int mid = (l + r) >> 1;
        if(!x) {
            return 0x3f3f3f3f;
        } else if(ql <= l && r <= qr) {
            return mn[x];
        } else if(qr <= mid) {
            return ask(lc[x], l, mid, ql, qr);
        } else if(ql >= mid + 1) {
            return ask(rc[x], mid + 1, r, ql, qr);
        } else {
            return min(ask(lc[x], l, mid, ql, mid), ask(rc[x], mid + 1, r, mid + 1, qr));
        }
    }
    NEK_TREE() {
        memset(mn, 0x3f, sizeof mn);
    }
} t_R, t_R_pri;

int main() {
    scanf("%d%d", &n, &q);
    scanf("%s", str + 1);
    for(int i = 1 ; i <= n ; ++ i) {
        str[n + i] = str[n - i + 1];
    }
    n *= 2;
    int pren = n;

    for(int i = 1 ; i <= n ; ++ i) {
        bak[i] = str[i];
    }
    build_sam();

    run_manacher();

    n = pren;

    auto ids = vector<vector<int> > (n + 10, vector<int> ());
    for(int i = 1 ; i <= n ; ++ i) {
        ids[i + R[i]].push_back(i);
    }
    for(int i = n ; i >= 1 ; -- i) {
        if(ids[i].empty()) {
            t_R.rt[i] = t_R.rt[i + 1];
        } else {
            int x = -1;
            int lst = t_R.rt[i + 1];
            for(int val: ids[i]) {
                x = ++ nek_cnt;
                t_R.modify(lst, x, 1, n, val);
                lst = x;
            }
            t_R.rt[i] = x;
        }
    }

    ids = vector<vector<int> > (n + 10, vector<int> ());
    for(int i = 1 ; i <= n ; ++ i) {
        if(R_pri[i] != -1) {
            ids[i + 1 + R_pri[i]].push_back(i);
        }
    }
    for(int i = n ; i >= 1 ; -- i) {
        if(ids[i].empty()) {
            t_R_pri.rt[i] = t_R_pri.rt[i + 1];
        } else {
            int x = -1;
            int lst = t_R_pri.rt[i + 1];
            for(int val: ids[i]) {
                x = ++ nek_cnt;
                t_R_pri.modify(lst, x, 1, n, val);
                lst = x;
            }
            t_R_pri.rt[i] = x;
        }
    }

    // printf("%d\n", nek_cnt);
    // return 0;

    while(q --) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        swap(l1, l2);
        swap(r1, r2);
        l2 = n / 2 + (n / 2 - l2 + 1);
        r2 = n / 2 + (n / 2 - r2 + 1);
        swap(l2, r2);
        // [l1, r1] 后缀，[l2, r2]前缀
        int lcs = min(min(r1 - l1 + 1, r2 - l2 + 1), getlcs(r1, r2));

        if(lcs == 0) {
            puts("0");
            continue;
        }
        int r = r1, l = r - lcs + 1;
        int ans = 0;
        int A, B;

        // odd
        A = ceil((l + r) / 2.0), B = r;
        if(A <= B) {
            int x = t_R.ask(t_R.rt[r], 1, n, A, B);
            if(x <= n) {
                ans = max(ans, 2 * (r - x) + 1);
            }
        }

        // even
        A = ceil((l + r - 1) / 2.0), B = r - 1;
        if(A <= B) {
            int x = t_R_pri.ask(t_R_pri.rt[r], 1, n, A, B);
            if(x <= n) {
                ans = max(ans, 2 * (r - x));
            }
        }
        printf("%d\n", -ans);
    }
}
