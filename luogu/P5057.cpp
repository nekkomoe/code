#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const int N = 200010 * 2;

int cnt[N * 4], l[N * 4], r[N * 4], lazy[N * 4];

char str[N];

void build(int id, int L, int R) {
    l[id] = L;
    r[id] = R;
    if(L == R) {
    } else {
        int M = (L + R) >> 1;
        build(id << 1, L, M );
        build(id << 1 | 1, M + 1, R);
        cnt[id] = cnt[id << 1] + cnt[id << 1 | 1];
    }
}

void push(int id) {
    if(lazy[id]) {
        cnt[id] = r[id] - l[id] + 1 - cnt[id];
        lazy[id << 1] ^= 1;
        lazy[id << 1 | 1] ^= 1;
        lazy[id] = 0;
    }
}

void modify(int id, int L, int R) {
    push(id);
    if(L <= l[id] && r[id] <= R) {
        lazy[id] ^= 1;
    } else if(!(l[id] > R || r[id] < L)){
        modify(id << 1, L, R);
        modify(id << 1 | 1, L, R);
        push(id << 1);
        push(id << 1 | 1);
        cnt[id] = cnt[id << 1] + cnt[id << 1 | 1];
    }
}

int ask(int id, int L, int R) {
    push(id);
    if(L <= l[id] && r[id] <= R) {
        return cnt[id];
    } else if(!(l[id] > R || r[id] < L)) {
        return ask(id << 1, L, R) + ask(id << 1 | 1, L, R);
    } else {
        return 0;
    }
}

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for(int i = 1, op, x, y ; i <= m ; i ++) {
        scanf("%d%d", &op, &x);
        if(op == 1) {
            scanf("%d", &y);
            modify(1, x, y);
        } else {
            printf("%d\n", ask(1, x, x));
        }
    }
}
