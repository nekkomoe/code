#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int tag[N], val[N], root[N], mxup[N], dis[N], lc[N], rc[N], tot;

int dep[N];

vector<int> g[N];
vector<pair<int, int> > pr[N];

int n, m;

void push(int x) {
    if(tag[x]) {
        val[x] += tag[x];
        tag[lc[x]] += tag[x], tag[rc[x]] += tag[x];
        tag[x] = 0;
    }
}

int merge(int x, int y) {
    if(!x || !y) return x | y;
    push(x), push(y);
    if(val[x] > val[y]) swap(x, y);
    rc[x] = merge(rc[x], y);
    if(dis[lc[x]] < dis[rc[x]]) swap(lc[x], rc[x]);
    dis[x] = dis[rc[x]] + 1;
    return x;
}

void dfs(int u) {
    
    for(auto t: pr[u]) {
        ++ tot;
        val[tot] = t.second;
        mxup[tot] = dep[t.first];
        root[u] = merge(root[u], tot);
    }
    
    int sum = 0;
    for(int v: g[u]) {
        dfs(v); push(root[v]); int vv = val[root[v]];
        tag[root[v]] += sum;
        tag[root[u]] += vv;
        sum += vv;
        root[u] = merge(root[u], root[v]);
    }
    
    while(root[u]) {
        push(root[u]);
        if(mxup[root[u]] > dep[u]) root[u] = merge(lc[root[u]], rc[root[u]]);
        else break;
    }
    
    if(!root[u]) {
        puts("-1");
        exit(0);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    dep[1] = 1;
    for(int i = 2 ; i <= n ; ++ i) {
        int fa; scanf("%d", &fa);
        g[fa].push_back(i);
        dep[i] = dep[fa] + 1;
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        pr[v].push_back(make_pair(u, w));
    }
    dfs(1);
    printf("%d\n", val[root[1]]);
}
