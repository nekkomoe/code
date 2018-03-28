#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

#define FN "lostmonkey"

const int N = 1010;

struct SEG {
    int val[N * 4], tag[N * 4];
    void push(int id) {
        if(tag[id]) {
            tag[id << 1] = tag[id];
            tag[id << 1 | 1] = tag[id];
            val[id] = tag[id];
            tag[id] = 0;
        }
    }
    void change(int id, int L, int R, int l, int r, int v) {
        push(id);
        int M = (L + R) >> 1;
        if(l <= L && R <= r) {
            tag[id] = v;
        } else if(L > r || R < l) {
            return;
        } else {
            change(id << 1, L, M, l, r, v);
            change(id << 1 | 1, M + 1, R, l, r, v);
        }
    }
    int ask(int id, int L, int R, int pos) {
        push(id);
        int M = (L + R) >> 1;
        if(L == R && L == pos) {
            return val[id];
        } else if(L > pos || R < pos) {
            return 0;
        } else {
            return max(ask(id << 1, L, M, pos), ask(id << 1 | 1, M + 1, R, pos));
        }
    }
} seg[N];

int n, m, k;

int main() {
    freopen(FN ".in", "r", stdin);
    freopen(FN ".out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1 ; i <= n ; i ++) {
        seg[i].change(1, 1, m, 1, m, 1);
    }
    for(int i = 1, x1, y1, x2, y2, v ; i <= k ; i ++) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
        for(int j = x1 ; j <= x2 ; j ++) {
            seg[j].change(1, 1, m, y1, y2, v + 1);
        }
    }
    for(int i = 1 ; i <= n ; i ++) {
        for(int j = 1 ; j <= m ; j ++) {
            printf("%d", seg[i].ask(1, 1, m, j) - 1);
        }
        puts("");
    }
}
