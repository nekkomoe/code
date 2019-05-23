#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 7e6 + 10;

#define lc (id << 1)
#define rc (id << 1 | 1)

vector<int> g[N];
int n, nds, pos[N], deg[N], ids[500010], ans[500010];

void build(int id, int l, int r) {
    int mid = (l + r) >> 1;
    nds = max(nds, id);
    if(l == r) {
        ids[l] = id;
        pos[id] = l;
    } else {
        g[id].push_back(lc);
        g[id].push_back(rc);
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }
}
void modify(int id, int l, int r, int ql, int qr, int nek) {
    int mid = (l + r) >> 1;
    if(ql <= l && r <= qr) {
        g[nek].push_back(id);
    } else if(qr <= mid) {
        modify(lc, l, mid, ql, qr, nek);
    } else if(ql >= mid + 1) {
        modify(rc, mid + 1, r, ql, qr, nek);
    } else {
        modify(lc, l, mid, ql, mid, nek);
        modify(rc, mid + 1, r, mid + 1, qr, nek);
    }
}

void runprog() {
    
    for(int i = 1 ; i <= nds ; ++ i) {
        deg[i] = pos[i] = ids[i] = 0;
        g[i].clear();
    }
    nds = 0;

    scanf("%d", &n);
    build(1, 1, n);
    for(int i = 1, x ; i <= n ; ++ i) {
        scanf("%d", &x);
        if(x != -1) {
            if(i + 1 <= x - 1) {
                modify(1, 1, n, i + 1, x - 1, ids[i]);
            }
            if(x <= n) {
                modify(1, 1, n, i, i, ids[x]);
            }
        }
    }

    int nek = n;
    queue<int> que;
    for(int i = 1 ; i <= nds ; ++ i) {
        for(int j: g[i]) {
            ++ deg[j];
        }
    }
    for(int i = 1 ; i <= nds ; ++ i) {
        if(!deg[i]) {
            que.push(i);
        }
    }
    while(que.size()) {
        int u = que.front(); que.pop();
        if(pos[u]) {
            ans[pos[u]] = nek --;
        }
        for(int v: g[u]) {
            if(! -- deg[v]) {
                que.push(v);
            }
        }
    }
    if(nek) {
        puts("-1");
    } else {
        for(int i = 1 ; i <= n ; ++ i) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t --) {
        runprog();
    }
}
