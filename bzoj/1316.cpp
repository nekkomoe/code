// 题意：求树上是否有一条长度为len的路径
// 题解：直接点分治就行
// 标签：点分治

#include <bits/stdc++.h>

using namespace std;

const int N = 21000;

int head[N], rest[N], to[N], tot, n, m, w[N];

void add(int u, int v, int ww) {
    to[++ tot] = v, w[tot] = ww, rest[tot] = head[u], head[u] = tot;
}

int root, f[N], ban[N], sz[N], size, query[N], ans[N], deep[N], kyo[N];

void getroot(int u, int fa) {
    sz[u] = 1;
    f[u] = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v] || v == fa) continue;
        getroot(v, u);
        sz[u] += sz[v];
        f[u] = max(f[u], sz[v]);
    }
    f[u] = max(f[u], size - sz[u]);
    if(f[u] < f[root]) root = u;
}

void getdeep(int u, int fa) {
    kyo[++ *kyo] = deep[u];
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v] || v == fa) continue;
        deep[v] = deep[u] + w[i];
        getdeep(v, u);
    }
}

int dfs(int u) {
    set<int> st;
    ban[u] = 1, st.insert(0);
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v]) continue;
        *kyo = 0, deep[v] = w[i], getdeep(v, u);
        
        for(int j = 1 ; j <= *kyo ; ++ j) {
            int &x = kyo[j];
            for(int k = 1 ; k <= m ; ++ k) {
                if(st.find(query[k] - x) != st.end()) ans[k] = 1;
            }
        }
        
        for(int j = 1 ; j <= *kyo ; ++ j) {
            int &x = kyo[j];
            st.insert(x);
        }
        
    }
    
    for(int i = 1 ; i <= m ; ++ i) {
        if(st.find(query[i]) != st.end()) ans[i] = 1;
    }
    
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v]) continue;
        size = sz[v], root = 0, getroot(v, 0);
        dfs(root);
    }
}

void sol() {
    f[root = 0] = (size = n) + 1;
    getroot(1, 0);
    dfs(root);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v, w ; i < n ; ++ i) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%d", &query[i]);
    }
    sol();
    for(int i = 1 ; i <= m ; ++ i) {
        puts(ans[i] ? "Yes" : "No");
    }
}
