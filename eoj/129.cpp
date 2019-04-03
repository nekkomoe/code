#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m, sum[N], sum_vir[N];

int fa[N], ch[N][2], rev[N];

int isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

int isrig(int x) {
    return ch[fa[x]][1] == x;
}

void upd(int x) {
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + sum_vir[x] + 1;
}

void push(int x) {
    if(rev[x]) {
        rev[ch[x][0]] ^= 1;
        rev[ch[x][1]] ^= 1;
        swap(ch[x][0], ch[x][1]);
        rev[x] = 0;
    }
}

void rot(int x) {
    int y = fa[x], z = fa[y], k = isrig(x);
    fa[x] = z; if(!isroot(y)) ch[z][isrig(y)] = x;
    fa[ch[y][k] = ch[x][!k]] = y;
    fa[ch[x][!k] = y] = x;
    upd(y), upd(x);
}

void go(int x) {
    if(!isroot(x)) go(fa[x]);
    push(x);
}
void splay(int x) {
    go(x);
    for( ; !isroot(x) ; rot(x)) {
        if(!isroot(fa[x])) {
            rot(isrig(fa[x]) == isrig(x) ? fa[x] : x);
        }
    }
}

void access(int x) {
    for(int y = 0 ; x ; y = x, x = fa[x]) {
        splay(x);
        sum_vir[x] += sum[ch[x][1]] - sum[y];
        ch[x][1] = y;
        upd(x);
    }
}

void makeroot(int x) {
    access(x);
    splay(x);
    rev[x] = 1;
}

void mkr(int x, int y) {
    makeroot(x), makeroot(y);
}

void link(int x, int y) {
    mkr(x, y);
    fa[x] = y;
    sum_vir[y] += sum[x];
    upd(y);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        sum[i] = 1;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        char str[10]; int x, y; scanf("%s%d%d", str, &x, &y);
        if(str[0] == 'A') {
            link(x, y);
        } else {
            mkr(x, y);
            printf("%lld\n", (ll) sum[x] * (sum[y] - sum[x]));
        }
    }
}
