#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 10;
int n, ans[N], cnt, len;
vector<int> g[N];

int dfs(int u, int fa) {
    int mx = 0, smx = 0;
    for(int v: g[u]) {
        if(v == fa) continue;
        int sv = dfs(v, u);
        if(sv >= mx) smx = mx, mx = sv;
        else if(sv >= smx) smx = sv;
    }
    if(mx + smx + 1 >= len) {
        ++ cnt;
        return 0;
    } else {
        return mx + 1;
    }
}

int get(int len) {
    cnt = 0, :: len = len, dfs(1, 0);
    return cnt;
}

void sol(int l, int r, int ql, int qr) {
    if(l > r) {
        return ;
    } else if(ql == qr) {
        for(int i = l ; i <= r ; ++ i) {
            ans[i] = ql;
        }
    } else {
        int mid = (l + r) >> 1;
        int s = ans[mid] = get(mid);
        sol(l, mid - 1, s, qr), sol(mid + 1, r, ql, s);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    sol(1, n, 0, n);
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
