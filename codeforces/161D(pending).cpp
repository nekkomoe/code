#pragma GCC optimize(2)
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

const int N = 21000;

typedef long long ll;

ll ans;

int head[N], rest[N], to[N], tot, n, m, w[N];

void add(int u, int v, int ww) {
    to[++ tot] = v, w[tot] = ww, rest[tot] = head[u], head[u] = tot;
}

int root, f[N], ban[N], sz[N], size, deep[N], kyo[N];

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
    map<int, int> st;
    ban[u] = 1, st[0] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(ban[v]) continue;
        *kyo = 0, deep[v] = w[i], getdeep(v, u);
        
        for(int j = 1 ; j <= *kyo ; ++ j) {
            int &x = kyo[j];
            ans += st[m - x];
        }
        
        for(int j = 1 ; j <= *kyo ; ++ j) {
            int &x = kyo[j];
            ++ st[x];
        }
        
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
        scanf("%d%d", &u, &v);
        add(u, v, 1), add(v, u, 1);
    }
    sol();
    cout << ans << endl;
}
