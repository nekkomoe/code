#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
 
#define lc (id << 1)
#define rc (id << 1 | 1)
 
int lef[N * 4], rig[N * 4], mx[N * 4], lefval[N * 4], rigval[N * 4];
 
void up(int id, int l, int r, int mid) {
    lefval[id] = lefval[lc], rigval[id] = rigval[rc];
    lef[id] = lef[lc], rig[id] = rig[rc];
    if(lef[lc] == mid - l + 1) {
        if(rigval[lc] < lefval[rc]) {
            lef[id] = lef[lc] + lef[rc];
        }
    }
    if(rig[rc] == r - mid) {
        if(rigval[lc] < lefval[rc]) {
            rig[id] = rig[rc] + rig[lc];
        }
    }
    mx[id] = max(mx[lc], mx[rc]);
    if(rigval[lc] < lefval[rc]) {
        mx[id] = max(mx[id], rig[lc] + lef[rc]);
    }
}
 
void modify(int id, int l, int r, int pos, int val) {
    int mid = (l + r) >> 1;
    if(l == r) {
        lefval[id] = rigval[id] = val;
        lef[id] = rig[id] = 1;
        mx[id] = 1;
        return ;
    } else if(pos <= mid) {
        modify(lc, l, mid, pos, val);
    } else {
        modify(rc, mid + 1, r, pos, val);
    }
    up(id, l, r, mid);
}
 
void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    if(l == r) {
        int x; scanf("%d", &x);
        lefval[id] = rigval[id] = x;
        lef[id] = rig[id] = 1;
        mx[id] = 1;
    } else {
        build(lc, l, mid);
        build(rc, mid + 1, r);
        up(id, l, r, mid);
    }
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    printf("%d\n", mx[1]);
    for(int i = 1, x, y ; i <= m ; ++ i) {
        scanf("%d%d", &x, &y);
        // cout << "x = " << x << " y = " << y << endl;
        modify(1, 1, n, x, y);
        printf("%d\n", mx[1]);
    }
}
