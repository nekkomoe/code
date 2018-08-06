#include <cstdio>
#include <cstring>
 
const int N = 110;
 
int n, T, atsch[N], gohm[N];
 
int head[N], rest[N * N], to[N * N], tot;
 
void add(int u, int v) {
    to[++ tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}
 
int mat[N], vis[N], cnt;
 
int dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(vis[v] != cnt) {
            vis[v] = cnt;
            if(!mat[v] || dfs(mat[v])) {
                mat[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
 
int main() {
    scanf("%d", &T);
    while(T --) {
        memset(head, 0, sizeof head), tot = 0;
        memset(mat, 0, sizeof mat);
        memset(vis, 0, sizeof vis);
        cnt = 0;
        int sum = 0;
        scanf("%d", &n);
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &atsch[i]);
        for(int i = 1 ; i <= n ; ++ i) scanf("%d", &gohm[i]);
        for(int i = 1 ; i <= n ; ++ i) sum += (atsch[i] && !gohm[i]) || !atsch[i];
        for(int i = 1, x ; i <= n ; ++ i) {
            for(int j = 1 ; j <= n ; ++ j) {
                scanf("%d", &x);
                if(i == j && atsch[i] && !gohm[i]) add(i, n + j);
                if(x && ((atsch[i] && !gohm[i]) || !atsch[i]) && atsch[j]) add(i, n + j);
            }
        }
        for(int i = 1 ; i <= n ; ++ i) ++ cnt, sum -= dfs(i);
        if(!sum) puts("^_^");
        else puts("T_T");
    }
}
