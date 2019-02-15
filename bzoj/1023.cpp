#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int N = 1e6 + 10;
 
int n, m, head[N], rest[N], to[N], tot; 
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
int f[N], ans, fa[N], dep[N];
int dfn[N], low[N], clk, a[N];
int que[N], l, r;
 
void runprog(int root, int x) {
    int size = dep[x] - dep[root] + 1;
//    printf("RT: %d %d, %d\n", root, x, dep[x] - dep[root] + 1);
////    for(int i = x ; ; i = fa[i]) {
////        a[size --] = f[i];
////        if(i == root) break;
////    }
    for(int i = x ; i != root ; i = fa[i]) a[size --] = f[i];
    a[size] = f[root];
 
    size = dep[x] - dep[root] + 1;
    for(int i = 1 ; i <= size ; ++ i) {
        a[size + i] = a[i];
    }
     
//    for(int i = 1 ; i <= 2 * size ; ++ i) printf("%d ", a[i]); puts(""); 
     
    que[l = r = 1] = 1;
    for(int i = 2 ; i <= 2 * size ; ++ i) {
        while(l <= r && i - que[l] > size / 2) ++ l;
        if(l <= r) {
            int j = que[l];
            ans = max(ans, a[i] + a[j] + i - j);
        } 
        while(l <= r && a[que[r]] - que[r] <= a[i] - i) -- r;
        que[++ r] = i;
    }
    for(int i = 2 ; i <= size ; ++ i) {
        f[root] = max(f[root], a[i] + min(i - 1, size - i + 1));
    }
}
 
void neko(int u) {
    dfn[u] = low[u] = ++ clk;
    dep[u] = dep[fa[u]] + 1;
     
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            fa[v] = u;
            neko(v);
            low[u] = min(low[u], low[v]);
        } else if(v != fa[u]) {
            low[u] = min(low[u], dfn[v]);
        }
        if(dfn[u] < low[v]) {
            ans = max(ans, f[u] + f[v] + 1);
            f[u] = max(f[u], f[v] + 1);
        }
    }
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(dfn[u] < dfn[v] && fa[v] != u) {
            runprog(u, v);
        }
    }
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        int k, u; scanf("%d%d", &k, &u);
        for(int j = 1 ; j < k ; ++ j) {
            int v; scanf("%d", &v);
            add(u, v), add(v, u);
            u = v;
        } 
    }
    neko(1);
    printf("%d\n", ans);
}
