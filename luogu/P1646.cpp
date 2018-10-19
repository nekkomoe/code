#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e6 + 10;
 
const int inf = 1000000000;
 
int n, m, s, t, head[N], rest[N], to[N], flow[N], dis[N], tot = 1;
 
void add(int u, int v, int f) {
    to[++ tot] = v, flow[tot] = f, rest[tot] = head[u], head[u] = tot;
}
 
void ins(int u, int v, int f) {
    add(u, v, f), add(v, u, 0);
}
 
void ins2(int u, int v, int f) {
    ins(u, v, f), ins(v, u, f);
}
 
bool bfs() {
    queue<int> q;
    memset(dis, -1, sizeof dis);
    dis[s] = 0;
    q.push(s);
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(flow[i] && dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}
 
int dfs(int u, int f) {
    if(u == t) return f;
    int use = 0;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!flow[i] || dis[v] != dis[u] + 1) continue;
        int a = dfs(v, min(f - use, flow[i]));
        use += a, flow[i] -= a, flow[i ^ 1] += a;
        if(use == f) break;
    }
    if(!use) dis[u] = -1;
    return use;
}
 
int dinic() {
    int res = 0;
    while(bfs()) res += dfs(s, inf);
    return res;
}
 
int mv[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
 
int id(int i, int j) {
    return (i - 1) * m + j;
}
 
int art[110][110], sci[110][110], same_art[110][110], same_sci[110][110], sum;
 
 
int main() {
    scanf("%d%d", &n, &m);
    s = n * m + 1, t = s + 1;
     
    for(int i = 1 ; i <= n ; ++ i) for(int j = 1 ; j <= m ; ++ j) {
        scanf("%d", &art[i][j]);
        sum += art[i][j], art[i][j] *= 2;
    }
     
    for(int i = 1 ; i <= n ; ++ i) for(int j = 1 ; j <= m ; ++ j) {
        scanf("%d", &sci[i][j]);
        sum += sci[i][j], sci[i][j] *= 2;
    }
     
    for(int i = 1 ; i < n ; ++ i) for(int j = 1 ; j <= m ; ++ j) {
        int x; scanf("%d", &x);
        sum += x;
        art[i][j] += x, art[i + 1][j] += x;
        ins2(id(i, j), id(i + 1, j), x);
    }
     
    for(int i = 1 ; i < n ; ++ i) for(int j = 1 ; j <= m ; ++ j) {
        int x; scanf("%d", &x);
        sum += x;
        sci[i][j] += x, sci[i + 1][j] += x;
        ins2(id(i, j), id(i + 1, j), x);
    }
     
    for(int i = 1 ; i <= n ; ++ i) for(int j = 1 ; j < m ; ++ j) {
        int x; scanf("%d", &x);
        sum += x;
        art[i][j] += x, art[i][j + 1] += x;
        ins2(id(i, j), id(i, j + 1), x);
    }
 
    for(int i = 1 ; i <= n ; ++ i) for(int j = 1 ; j < m ; ++ j) {
        int x; scanf("%d", &x);
        sum += x;
        sci[i][j] += x, sci[i][j + 1] += x;
        ins2(id(i, j), id(i, j + 1), x);
    }
     
    for(int i = 1 ; i <= n ; ++ i) for(int j = 1 ; j <= m ; ++ j) {
        ins(s, id(i, j), art[i][j]);
        ins(id(i, j), t, sci[i][j]);
    }
     
    printf("%d\n", sum - dinic() / 2);
}
