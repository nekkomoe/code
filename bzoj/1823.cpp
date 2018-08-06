// 2-sat

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
int n, m;
 
const int N = 200010;
 
int head[N], rest[N], to[N], tot;
 
void add(int u, int v) {
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
int dfn[N], low[N], id[N], cnt, clk, ins[N];
 
stack<int> s;
 
void cls() {
    memset(head, 0, sizeof head), tot = 0;
    memset(dfn, 0, sizeof dfn), cnt = clk = 0;
    memset(id, 0, sizeof id);
}
 
void dfs(int u) {
    low[u] = dfn[u] = ++ clk;
    s.push(u), ins[u] = 1;
    for(int i = head[u] ; i ; i = rest[i]) {
        int v = to[i];
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int v;
        ++ cnt;
        do {
            v = s.top(); s.pop();
            ins[v] = 0;
            id[v] = cnt;
        } while(v != u);
    }
}
 
void tarjan() {
    for(int i = 2 ; i <= 2 * n + 1 ; ++ i) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
}
 
#define get(ch, x) (2 * x + (ch == 'm'))
 
void sol() {
    cls();
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= m ; ++ i) {
        char c1, c2; int x1, x2;
        getchar();
        scanf("%c%d %c%d", &c1, &x1, &c2, &x2);
        int p1 = get(c1, x1), p2 = get(c2, x2);
        add(p1 ^ 1, p2), add(p2 ^ 1, p1);
    }
     
    tarjan();
    for(int i = 2 ; i <= 2 * n ; i += 2) {
        if(id[i] == id[i ^ 1]) return puts("BAD"), void();
    }
    puts("GOOD");
}
 
int main() {    
    for(int T = scanf("%d", &T) - 1 + T ; T -- ; ) sol();
}