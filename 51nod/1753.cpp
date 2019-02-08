#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int base = 137;
const int N = 300000 + 10;

int n, fa[30]; char str[N];

int get(int x) {
    return x == fa[x] ? x : fa[x] = get(fa[x]);
}

ull pw[N];
ull hs[N][30];

ull ask(int l, int r) {
    ull res = 0;
    for(int c = 1 ; c <= 26 ; ++ c) {
        ull val = hs[r][c] - hs[l - 1][c] * pw[r - l + 1];
        res += val * get(c);
    }
    return res;
}

void init() {
    pw[0] = 1;
    for(int i = 1 ; i <= n ; ++ i) {
        pw[i] = pw[i - 1] * base;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int c = 1 ; c <= 26 ; ++ c) {
            hs[i][c] = hs[i - 1][c] * base + (str[i] - 'a' + 1 == c);
        }
    }
}

int runprog(int l1, int r1, int l2, int r2) {
    if(r1 - l1 != r2 - l2) return 0;
    if(ask(l1, r1) == ask(l2, r2)) return 1;
    int len = r1 - l1 + 1;
    int l = 1, r = len;
    while(l <= r) {
        int mid = (l + r) >> 1;
        
        int lef = ask(l1, l1 + mid - 1 - 1) == ask(l2, l2 + mid - 1 - 1);
        int rig = ask(l1 + mid, r1) == ask(l2 + mid, r2);

        if(lef && rig) {
            return 1;
        }
        if(lef) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }

    }
    return 0;
}

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    init();
    int q; scanf("%d", &q);
    while(q --) {
        int k, l1, r1, l2, r2;
        scanf("%d%d%d%d%d", &k, &l1, &r1, &l2, &r2);
        for(int i = 1 ; i <= 26 ; ++ i) {
            fa[i] = i;
        }
        while(k --) {
            char tmp[10]; scanf("%s", tmp);
            int u = tmp[0] - 'a' + 1, v = tmp[1] - 'a' + 1;
            fa[get(u)] = get(v);
        }
        puts(runprog(l1, r1, l2, r2) ? "YES" : "NO");
    }
}
