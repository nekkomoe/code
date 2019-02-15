#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
 
const int N = 2e5 + 10;
 
int n, m, head[N], rest[N], to[N], w[N], tot;
 
void add(int u, int v, int val) {
    to[++ tot] = v, w[tot] = val, rest[tot] = head[u], head[u] = tot;
}
 
int sz[N], f[N] = { 0x3f3f3f3f }, root, size, ban[N];
 
void getrt(int u, int fa) {
    sz[u] = 1, f[u] = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa || ban[v]) continue;
        getrt(v, u);
        sz[u] += sz[v];
        f[u] = max(f[u], sz[v]);
    } 
    f[u] = max(f[u], size - sz[u]);
    if(f[u] < f[root]) root = u;
}
 
const int NNN = 1e6 + 10;
 
int cnt, pts_cnt, dis[N], dis_cnt, lg[NNN];
 
struct PR { int l, r, dis; } pr[N]; int pr_cnt;
 
int mx[NNN][21];
 
struct T {
    int l, r, mxpos, val, pos;
} pts[NNN]; // ?
 
bool operator < (T a, T b) {
    return pr[a.mxpos].dis + pr[a.pos].dis < pr[b.mxpos].dis + pr[b.pos].dis;
}
 
 
int getmax(int a, int b) {
    return pr[a].dis > pr[b].dis ? a : b;
}
 
int askmax(int l, int r) {
    if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return getmax(mx[l][k], mx[r - (1 << k) + 1][k]);
}
 
void init() {
    for(int i = 1 ; i <= pr_cnt ; ++ i) {
        mx[i][0] = i;
        if(i > 1) lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1 ; j <= 20 ; ++ j) {
        for(int i = 1 ; i + (1 << j) - 1 <= pr_cnt ; ++ i) {
            mx[i][j] = getmax(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
}
 
void dfs(int u, int fa, int len = 0) {
    dis[++ dis_cnt] = len;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v == fa || ban[v]) continue;
        dfs(v, u, len + w[i]);
    }
}
 
void sol(int u) {
    ban[u] = 1;
  
    int L = pr_cnt + 1;
     
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v]) continue;
        dis_cnt = 0;
        dfs(v, u, w[i]);
        int R = pr_cnt;
        for(int j = 1 ; j <= dis_cnt ; ++ j) {
            pr[++ pr_cnt] = (PR) { L, R, dis[j] };
        }
    }
    int R = pr_cnt;
    pr[++ pr_cnt] = (PR) { L, R, 0 };
    
    // assert(pr_cnt < NNN);

    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v]) continue;
        root = 0, size = sz[v], getrt(v, 0), sol(root);
    }
}

priority_queue<T> pq;
 
int main() {
     
//    freopen("data.in", "r", stdin);
     
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i < n ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }

    root = 0, size = n, getrt(1, 0), sol(root);

    // return 0;

    init();
    for(int i = 1 ; i <= pr_cnt ; ++ i) {
        if(pr[i].l <= pr[i].r) {
            pq.push((T) { pr[i].l, pr[i].r, askmax(pr[i].l, pr[i].r), pr[i].dis, i });
        }
//        printf("pts %d, can be save to [%d, %d], max is %d, self val = %d\n", i, pr[i].l, pr[i].r, askmax(pr[i].l, pr[i].r), pr[i].dis);
    }

    while(m --) {
        T top = pq.top(); pq.pop();
        printf("%d\n", pr[top.mxpos].dis + top.val);
        int mxpos = top.mxpos;
        if(top.l <= mxpos - 1) {
            pq.push((T) { top.l, mxpos - 1, askmax(top.l, mxpos - 1), top.val, top.pos });
        }
        if(mxpos + 1 <= top.r) {
            pq.push((T) { mxpos + 1, top.r, askmax(mxpos + 1, top.r), top.val, top.pos });
        }
    }
}
