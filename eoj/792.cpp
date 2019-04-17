#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 50000 + 10;

int n, S, T;
int lc[N], rc[N];

ld rk[N];
int sam[N], bel[N], sz[N];

vector<int> nek;

int equ(int u, int v) {
    return bel[u] == bel[v];
}
int cmp(int u, int v) {
    return rk[bel[u]] < rk[bel[v]];
}

int get(int i, int l, int r) {
    int u = lc[i], v = rc[i];
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        int t = nek[mid];
        if(equ(u, lc[t]) && equ(v, rc[t])) {
            ++ sam[bel[i] = bel[t]];
            return -1;
        }
        if(cmp(u, lc[t]) || (equ(u, lc[t]) && cmp(v, rc[t]))) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    return l;
}

void ins(int pos, int i) {
    rk[i] = (rk[nek[pos]] + rk[nek[pos + 1]]) / 2;
    nek.insert(nek.begin() + pos + 1, i);
    sz[i] = sz[nek[pos]];
    bel[i] = i;
    sam[i] = 1;
}

int main() {
    scanf("%d", &n);
    S = 0, T = n + 1;

    bel[S] = 0;
    lc[S] = rc[S] = S;
    rk[S] = 0;
    sz[S] = 1;
    sam[S] = 1;

    bel[T] = T;
    lc[T] = rc[T] = T;
    rk[T] = 1;
    sz[T] = 2;
    sam[T] = 1;

    nek.push_back(S);
    nek.push_back(T);
    for(int i = 1 ; i <= n ; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        lc[i] = u, rc[i] = v;
        int pos = get(i, 0, nek.size() - 1);
        
        if(pos != -1) {
            if(equ(lc[i], lc[nek[pos]]) && equ(rc[i], rc[nek[pos]])) {
                ++ sam[bel[i] = bel[nek[pos]]];
            } else {
                ins(pos, i);
            }
        }

        int ans = sz[bel[i]];

        for(int j = (i - 1) / 30 * 30 + 1 ; j <= i ; ++ j) {
            if(equ(j, i) || cmp(j, i)) {
                ++ ans;
            }
        }

        printf("%d\n", ans);

        if(i == n || i % 30 == 0) {
            for(int j = 0 ; j < nek.size() ; ++ j) {
                sz[nek[j]] = (j ? sz[nek[j - 1]] : 0) + sam[nek[j]];
                rk[nek[j]] = j;
            }
        }
    }
}

