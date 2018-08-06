#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e5;
 
int n, m, cnt = 1, ch[N][30], pos[N], fa[N], fail[N];
 
char s[N];
 
queue<int> q;
 
int head[N], rest[N], to[N];
 
void ins(int u, int v) {
    static int tot = 0;
    to[++ tot] = v, rest[tot] = head[u], head[u] = tot;
}
 
void build() {
    q.push(1);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i = 0 ; i < 26 ; ++ i) {
            int v = ch[u][i];
            if(v) {
                int k = fail[u];
                while(!ch[k][i]) k = fail[k];
                fail[v] = ch[k][i];
                q.push(v);
            }
        }
    }
    for(int i = 1 ; i <= cnt ; ++ i) {
        ins(fail[i], i);
    }
}
 
int l[N], r[N], clk;
 
void dfs(int u) {
    l[u] = ++ clk;
    for(int i = head[u] ; i ; i = rest[i]) dfs(to[i]);
    r[u] = ++ clk;
}
 
int val[N], frs[N], nxt[N];
 
int ans[N];
 
int a[N];
 
void add(int i, int v) { for( ; i <= clk ; i += i & -i) a[i] += v; }
 
int ask(int i) { int res = 0; for( ; i ; i -= i & -i) res += a[i]; return res; }
 
void sol() {
    add(l[1], 1);
    for(int i = 1, id = 0, p = 1 ; i <= n ; ++ i) {
        int c = s[i];
        if(c == 'P') {
            for(int x = frs[++ id] ; x ; x = nxt[x]) {
                int y = pos[val[x]];
                ans[x] = ask(r[y]) - ask(l[y] - 1);
            }
        } else if(c == 'B') {
            add(l[p], -1), p = fa[p];
        } else {
            add(l[p = ch[p][c - 'a']], 1);
        }
    }
}
 
int main() {
 
    scanf("%s", s + 1), n = strlen(s + 1);
     
    for(int i = 0 ; i < 26 ; ++ i) ch[0][i] = 1;
     
    for(int i = 1, id = 0, p = 1 ; i <= n ; ++ i) {
        int c = s[i];
        if(c == 'P') {
            pos[++ id] = p;
        } else if(c == 'B') {
            p = fa[p];
        } else {
            c -= 'a';
            if(!ch[p][c]) {
                ch[p][c] = ++ cnt;
                fa[cnt] = p;
            }
            p = ch[p][c];
        }
    }
     
    build();
     
    scanf("%d", &m);
    for(int i = 1, x, y ; i <= m ; ++ i) {
        scanf("%d%d", &x, &y);
        nxt[i] = frs[y];
        frs[y] = i;
        val[i] = x;
    }
     
    dfs(0);
    sol();
     
    for(int i = 1 ; i <= m ; ++ i) {
        printf("%d\n", ans[i]);
    }
}
