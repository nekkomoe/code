#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2010;

char a[N][N];

vector<int> g[N];

int fa[N]; int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }
int d[N];

int val[N], vis[N];
int n, m;
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n + m ; ++ i) fa[i] = i; 
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", a[i] + 1);
        for(int j = 1 ; j <= m ; ++ j) {
            if(a[i][j] == '=') {
                fa[get(i)] = get(n + j);
            }
        }
    }
    for(int i = 1 ; i <= n ; ++ i) {
        for(int j = 1 ; j <= m ; ++ j) {
            int u = get(i), v = get(n + j);
            if(a[i][j] == '>') {
                g[v].push_back(u);
                ++ d[u];
            } else if(a[i][j] == '<') {
                g[u].push_back(v);
                ++ d[v];
            }
        }
    }
    
    queue<int> q;
    for(int i = 1 ; i <= n + m ; ++ i) {
        int u = get(i);
        if(d[u] == 0 && vis[u] == 0) {
            q.push(u);
            vis[u] = 1;
        }
    }
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < g[u].size() ; ++ i) {
            int v = g[u][i];
            val[v] = max(val[v], val[u] + 1); 
            if(-- d[v] == 0) {
                q.push(v);
            }
        }
    }
    for(int i = 1 ; i <= n + m ; ++ i)
        if(d[i]) {
            puts("No");
            return 0;
        }
    puts("Yes");
    for(int i = 1 ; i <= n ; ++ i) {
        printf("%d ", val[get(i)] + 1); 
    } puts("");
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%d ", val[get(n + i)] + 1);
    } 
}
