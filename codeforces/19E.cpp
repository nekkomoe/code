#include "bits/stdc++.h"
 
using namespace std;
 
const int N = 4e5 + 10;
 
int head[N], rest[N], from[N], to[N], tot = 1;
void add(int u, int v) {
    from[++ tot] = u, to[tot] = v, rest[tot] = head[u], head[u] = tot;
}
int n, m;
int cnt[N][2], top[2], dep[N], vis[N];
 
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(vis[i]) continue; vis[i ^ 1] = 1;
        if(dep[v]) {
            int t = (dep[u] - dep[v] + 1) & 1;
            ++ top[t];
            ++ cnt[u][t];
            -- cnt[v][t];
        } else {
            dfs(v, u);
            cnt[u][0] += cnt[v][0];
            cnt[u][1] += cnt[v][1];
        }
    }
}

namespace check_bin {
int col[N], flag;
void dfs(int u, int c) {
    col[u] = c;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(col[v] == col[u]) {
            flag = 1;
            return ;
        }
        if(col[v] == 0) {
            dfs(v, 3 - c);
        }
    }
}
void sol() {
    for(int i = 1 ; i <= n ; ++ i) {
        if(col[i] == 0) {
            dfs(i, 1);
        }
    }
    if(flag) {
        return ;
    }
    printf("%d\n", m);
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%d ", i);
    }
    exit(0);
}
}
 
int main() {
    int ans = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i <= m ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }

    check_bin :: sol();

    for(int i = 1 ; i <= n ; ++ i) {
        if(!dep[i]) {
            dfs(i, 0);
        }
    }
    vector<int> output;
    for(int i = 2 ; i <= tot ; i += 2) {
        int u = from[i], v = to[i];
        if(dep[u] > dep[v]) swap(u, v);
        if(dep[u] + 1 == dep[v]) {
            if(cnt[v][0] == 0 && cnt[v][1] == top[1]) {
                output.push_back(i / 2);
                ++ ans;
            }
        } else {
            if(((dep[v] - dep[u] + 1) & 1) && top[1] == 1) {
                output.push_back(i / 2);
                ++ ans;
            }
        }
    }
    printf("%d\n", ans);
    sort(output.begin(), output.end());
    for(int i = 0 ; i < int(output.size()) ; ++ i) {
        printf("%d ", output[i]);
    }
}

