#include <bits/stdc++.h>

using namespace std;

int n, m, c1, c2;

char s[60][60];

const int N = 1000 + 10;

int head[N], rest[N], to[N], tot = 1;

void ins(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}

int a[60][60], b[60][60];

int vis[N], T, ans, mat[N];

int dfs(int u) {
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(vis[v] != T) {
            vis[v] = T;
            if(!mat[v] || dfs(mat[v])) {
                mat[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s[i] + 1);
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[i][j] == '*') {
                a[i][j] = (j > 1 && s[i][j - 1] == '*' ? a[i][j - 1] : ++ c1);
                b[i][j] = (i > 1 && s[i - 1][j] == '*' ? b[i - 1][j] : ++ c2);
            }
        }
    }

    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            if(s[i][j] == '*') {
                ins(a[i][j], b[i][j] + c1);
            }
        }
    }

    for(int i = 1 ; i <= c1 ; ++ i) {
        ++ T;
        if(dfs(i)) ++ ans;
    }

    printf("%d\n", ans);
}
