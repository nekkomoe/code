#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 110000;
 
int n, m, bit[N], a[N], L[N], R[N];
 
void add(int i, int v) {
    for( ; i <= 100000 ; i += i & -i) if(v) bit[i] = max(bit[i], v); else bit[i] = 0;
}
 
int query(int i) {
    int ret = 0;
    for( ; i ; i -= i & -i) ret = max(ret, bit[i]);
    return ret;
}
 
int ans[N];
 
struct Q {
    int l, r, id;
} q[N];
 
bool operator < (Q x, Q y) {
    return x.l == y.l ? x.id < y.id : x.l < y.l;
}
 
void sol(int l, int r) {
    if(l == r) {
        ans[l] = max(ans[l], 1);
        return;
    }
    int m = (l + r) >> 1;
    sol(l, m);
    for(int i = l ; i <= r ; ++ i) {
        if(i <= m) q[i] = (Q) {a[i], R[i], i};
        else q[i] = (Q) {L[i], a[i], i};
    }
    sort(q + l, q + r + 1);
    for(int i = l ; i <= r ; ++ i) {
        if(q[i].id <= m) add(q[i].r, ans[q[i].id]);
        else ans[q[i].id] = max(ans[q[i].id], query(q[i].r) + 1);
    }
    for(int i = l ; i <= r ; ++ i) {
        if(q[i].id <= m) add(q[i].r, 0);
    }
    sol(m + 1, r);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]), L[i] = R[i] = a[i];
    for(int i = 1, x, y ; i <= m ; ++ i) scanf("%d%d", &x, &y), L[x] = min(L[x], y), R[x] = max(R[x], y);
    sol(1, n);
    for(int i = 1 ; i <= n ; ++ i) ans[0] = max(ans[0], ans[i]);
    printf("%d\n", ans[0]);
}
