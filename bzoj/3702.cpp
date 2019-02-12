%:pragma GCC optimize(2)
;
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
 
using namespace std;
 
const int N = 1010000;
 
int tree[N][2], cnt, tot, rt, n, ch[N * 4][2], sum[N * 4], root[N];
 
long long ans0, ans1, ans;
 
#define lc ch[id][0]
 
#define rc ch[id][1]
 
void update(int id) {
    sum[id] = sum[lc] + sum[rc];
}
 
void modify(int &id, int l, int r, int pos) {
    if(!id) id = ++ tot;
    int mid = (l + r) >> 1;
    if(l == r) ++ sum[id];
    else if(pos <= mid) modify(lc, l, mid, pos), update(id);
    else modify(rc, mid + 1, r, pos), update(id);
}
 
int merge(int x, int y) {
    if(!x || !y) return x | y;
    ans0 += (long long)sum[ch[x][0]] * sum[ch[y][1]];
    ans1 += (long long)sum[ch[x][1]] * sum[ch[y][0]];
    ch[x][0] = merge(ch[x][0], ch[y][0]);
    ch[x][1] = merge(ch[x][1], ch[y][1]);
    update(x);
    return x;
}
 
int read() {
    int x, id = ++ cnt;
    scanf("%d", &x);
    if(x) modify(root[id], 1, n, x);
    else tree[id][0] = read(), tree[id][1] = read();
    return id;
}
 
void dfs(int u) {
    if(!u || !(tree[u][0] || tree[u][1])) return;
    dfs(tree[u][0]);
    dfs(tree[u][1]);
    ans0 = ans1 = 0;
    root[u] = merge(root[tree[u][0]], root[tree[u][1]]);
    ans += min(ans0, ans1);
}
 
int main() {
    scanf("%d", &n);
    rt = read();
    dfs(rt);
    printf("%lld\n", ans);
    return 0;
}
