#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
const int N = 200010;
 
char type[N][5];
 
int n, m, head[N], to[N], rest[N], tot, code[N], ans[N], cnt[N], acc[N], fa[N];
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
void dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(v != fa[u]) {
            fa[v] = u;
            dfs(v);
        }
    }
}
 
int find(int x) {
    return x == acc[x] ? x : acc[x] = find(acc[x]);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    cnt[1] = 1;
    dfs(1);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s%d", type[i], &code[i]);
        if(type[i][0] == 'C') ++ cnt[code[i]];
    }
    for(int i = 1 ; i <= n ; ++ i) {
        acc[i] = cnt[i] ? i : fa[i];
    }
    for(int i = m ; i >= 1 ; -- i) {
        if(type[i][0] == 'Q') {
            ans[i] = find(code[i]);
        } else {
            -- cnt[code[i]];
            if(!cnt[code[i]]) {
                acc[find(code[i])] = acc[fa[code[i]]];
            }
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        if(type[i][0] == 'Q') {
            printf("%d\n", ans[i]);
        }
    }
}
