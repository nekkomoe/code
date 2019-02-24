#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e6 + 10;

int n;

int a[N], b[N];

vector<int> g[N]; 

int d[N];
int vis[N];

int fa[N];
int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
int lc[N], rc[N];

void dfs(int u) {
    if(u <= n) printf("%d ", u);
    else {
        dfs(lc[u]);
        dfs(rc[u]);
    }
}

int root, nd_cnt; 

int main() {
    scanf("%d", &n);
    nd_cnt = n;
    for(int i = 1 ; i <= 2 * n ; ++ i) fa[i] = i;
    int m = n - 1;
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d%d", &a[i], &b[i]);
        int x = a[i], y = b[i];
        x = get(x), y = get(y);
        int z = ++ nd_cnt;
        lc[z] = x, rc[z] = y;
        root = z;
        fa[x] = z, fa[y] = z;
    } 
    dfs(root);
}
