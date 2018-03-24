#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
 
using namespace std;
 
int n, m;
 
char mp[60][60];
 
int rowid[60][60], colid[60][60], rowcnt, colcnt;
 
const int N = 110000;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int match[N], vis[N], T;
 
bool dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(vis[v] != T) {
            vis[v] = T;
            if(!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
 
int ans;
 
void dfsrow(int i, int j, int cnt) {
    if(i < 1 || i > n || rowid[i][j] || mp[i][j] == '#') return;
    rowid[i][j] = cnt;
    dfsrow(i - 1, j, cnt);
    dfsrow(i + 1, j, cnt);
}
 
void dfscol(int i, int j, int cnt) {
    if(j < 1 || j > m || colid[i][j] || mp[i][j] == '#') return;
    colid[i][j] = cnt;
    dfscol(i, j - 1, cnt);
    dfscol(i, j + 1, cnt);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", mp[i] + 1);
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(mp[i][j] == '*') {
                if(!rowid[i][j]) dfsrow(i, j, ++ rowcnt);
                if(!colid[i][j]) dfscol(i, j, ++ colcnt);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(mp[i][j] == '*') {
                add(rowid[i][j], colid[i][j]);
            }
        }
    }
    for(int i = 1 ; i <= rowcnt ; ++ i) {
        ++ T;
        ans += dfs(i);
    }
    printf("%d\n", ans);
    return 0;
}
